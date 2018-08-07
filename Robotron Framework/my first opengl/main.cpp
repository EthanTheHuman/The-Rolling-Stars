// Dependencies
#include <iostream>
#include "ShaderLoader.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <iterator>
#include <map>

#include "Camera.h"
#include "GameManager.h"
#include "Sound.h"
#include "Sprite.h"
#include "Model.h"
#include "TextLabel.h"
#include "Utils.h"
#include "CubeMap.h"
#include "dependencies\FMOD\fmod.hpp"

//Library Includes
#include <Windows.h>
#include <cassert>
//#include <vld.h>
#include <thread>

//Local Includes
#include "consoletools.h"
#include "network.h"
#include "client.h"
#include "server.h"
#include "InputLineBuffer.h"
#include <functional>

// make sure the winsock lib is included...
#pragma comment(lib,"ws2_32.lib")

// Namespace
using namespace std;

// Functions
void init();
void render();

void Keyboard_Down(unsigned char key, int x, int y);
void Keyboard_Up(unsigned char key, int x, int y);
void KeyboardUpdate();

void update();

void StartNetwork();
void UpdateNetwork();
void ShutDownNetwork();
void ChangeJoinNames(std::vector<string> _Names);
void MovePlayerOne(glm::vec3 _NewPos);
void MoveNetworkPlayer(glm::vec3 _NewPos);

//Global Var
Camera * MyCamera;
Model * MyPyramid;
Sprite * KarateGuy1;
Sprite * KarateGuy2;

TextLabel * label;

CubeMap * MySkybox;

unsigned char KeyState[255]; // Global

char* _pcPacketData = 0; //A local buffer to receive packet data info

char _cIPAddress[MAX_ADDRESS_LENGTH]; // An array to hold the IP Address as a string
//ZeroMemory(&_cIPAddress, strlen(_cIPAddress));

unsigned char _ucChoice;
EEntityType _eNetworkEntityType;
CInputLineBuffer _InputBuffer(MAX_MESSAGE_LENGTH);

std::thread _ClientReceiveThread, _ServerReceiveThread;

//Get the instance of the network
CNetwork& _rNetwork = CNetwork::GetInstance();

//A pointer to hold a client instance
CClient* _pClient = nullptr;
//A pointer to hold a server instance
CServer* _pServer = nullptr;

bool ServerChosen = false;

// Main function
int main(int argc, char **argv)
{
	// OpenGL Window Creation
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(SRCWIDTH, SRCHEIGHT);
	glutCreateWindow("Double Damage!");

	//Updated Keyboard Functions
	glutKeyboardFunc(Keyboard_Down);
	glutKeyboardUpFunc(Keyboard_Up);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 0.0, 1.0); //clear red

	// Initialisation
	glewInit();
	init();

	// Functions

	// register callbacks
	glutDisplayFunc(render);
	glutIdleFunc(update);
	glutMainLoop();

	return(0);
}

// Initialise Function
void init()
{
	GameManager::GetInstance()->SwitchScene(0);
	//---------------------------------------------------------------
}

// Render Function
void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0); // clear red

	GameManager::GetInstance()->update();
	GameManager::GetInstance()->render();
	glutSwapBuffers();
}

// Update Function
void update()
{
	glutPostRedisplay();
	//Updated Move Function
	GameManager::GetInstance()->CurrentSceneClass()->MoveCharacter(KeyState);
	KeyboardUpdate();
	UpdateNetwork();
	if (!_rNetwork.IsOnline()) {
		if (GameManager::GetInstance()->CurrentScene == 0)
		{
			//Host
			if (GameManager::GetInstance()->CurrentSceneClass()->Networkmode == 1)
			{
				_eNetworkEntityType = SERVER;
				StartNetwork();
			}
			//Join
			else if (GameManager::GetInstance()->CurrentSceneClass()->Networkmode == 2)
			{
				_eNetworkEntityType = CLIENT;
				StartNetwork();
				_pClient->Broadcast();
			}
		}
	}
	else {
		if (GameManager::GetInstance()->CurrentSceneClass()->Networkmode == 0) {
			ShutDownNetwork();
		}
		if (_eNetworkEntityType == CLIENT) {
			if (ServerChosen == false) {
				GameManager::GetInstance()->CurrentSceneClass()->ChangeNames(_pClient->RetreveBroadcast());
				if (GameManager::GetInstance()->CurrentSceneClass()->ServerChosen != 0) {
					ServerChosen = _pClient->HandShake(GameManager::GetInstance()->CurrentSceneClass()->ServerChosen - 1);
				}
			}
			else {
				if (GameManager::GetInstance()->CurrentSceneClass()->GameStart == false) {
					GameManager::GetInstance()->CurrentSceneClass()->ChangeHostNames(_pClient->RetrevePlayers());
				}
			}
		}
		else if (_eNetworkEntityType == SERVER) {
			if (GameManager::GetInstance()->CurrentSceneClass()->GameStart == false) {
				GameManager::GetInstance()->CurrentSceneClass()->ChangeHostNames(_pServer->RetrevePlayers());
			}
		}
	}
}

//Updated Keyboard Functions v3
void Keyboard_Down(unsigned char key, int x, int y) { if (KeyState[key] != INPUT_HOLD) { KeyState[key] = INPUT_FIRST_PRESS; } }
void Keyboard_Up(unsigned char key, int x, int y) { if (KeyState[key] != INPUT_RELEASED) {KeyState[key] = INPUT_FIRST_RELEASE; } }

void KeyboardUpdate() {
	for (int i = 0; i < 255; i++) {
		if (KeyState[i] == INPUT_FIRST_PRESS) {
			KeyState[i] = INPUT_HOLD;
		}
	}
	for (int i = 0; i < 255; i++) {
		if (KeyState[i] == INPUT_FIRST_RELEASE) {
			KeyState[i] = INPUT_RELEASED;
		}
	}
}

void StartNetwork()
{
	_pcPacketData = new char[MAX_MESSAGE_LENGTH];
	strcpy_s(_pcPacketData, strlen("") + 1, "");

	_rNetwork.StartUp();
	if (!_rNetwork.GetInstance().Initialise(_eNetworkEntityType))
	{
		std::cout << "Unable to initialise the Network........Press any key to continue......";
		_getch();
		return;
	}

	//Run receive on a separate thread so that it does not block the main client thread.
	if (_eNetworkEntityType == CLIENT) //if network entity is a client
	{

		_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ClientReceiveThread = std::thread(&CClient::ReceiveData, _pClient, std::ref(_pcPacketData));
	}

	//Run receive of server also on a separate thread 
	else if (_eNetworkEntityType == SERVER) //if network entity is a server
	{

		_pServer = static_cast<CServer*>(_rNetwork.GetInstance().GetNetworkEntity());
		_ServerReceiveThread = std::thread(&CServer::ReceiveData, _pServer, std::ref(_pcPacketData));
	}
}

void UpdateNetwork() {
	if (_rNetwork.IsOnline()) {
		if (_eNetworkEntityType == CLIENT) //if network entity is a client
		{
			_pClient = static_cast<CClient*>(_rNetwork.GetInstance().GetNetworkEntity());
			if (_pClient != nullptr)
			{
				//If the message queue is empty 
				if (_pClient->GetWorkQueue()->empty())
				{
					//Don't do anything
				}
				else
				{
					//Retrieve off a message from the queue and process it
					std::string temp;
					_pClient->GetWorkQueue()->pop(temp);
					_pClient->ProcessData(const_cast<char*>(temp.c_str()));
				}
			}

		}
		else //if you are running a server instance
		{
			if (_pServer != nullptr)
			{
				if (!_pServer->GetWorkQueue()->empty())
				{
					_rNetwork.GetInstance().GetNetworkEntity()->GetRemoteIPAddress(_cIPAddress);
					//Retrieve off a message from the queue and process it
					_pServer->GetWorkQueue()->pop(_pcPacketData);
					_pServer->ProcessData(_pcPacketData);
				}
			}
		}
	}
}

void ShutDownNetwork() {
	if (_pClient != nullptr) {
		_pClient->SwitchOff();
		if (_ClientReceiveThread.joinable()) {
			_ClientReceiveThread.join();
		}
		_pClient = nullptr;
	}
	if (_pServer != nullptr) {
		_pServer->SwitchOff();
		if (_ServerReceiveThread.joinable()) {
			_ServerReceiveThread.join();
		}
		_pServer = nullptr;
	}
	//Shut Down the Network
	_rNetwork.ShutDown();
	_rNetwork.DestroyInstance();
	delete[] _pcPacketData;
	return;
}

void ChangeJoinNames(std::vector<string> _Names)
{
	GameManager::GetInstance()->CurrentSceneClass()->ChangeNames(_Names);
}

void ChangeHostNames(std::vector<string> _Names)
{
	GameManager::GetInstance()->CurrentSceneClass()->ChangeHostNames(_Names);
}

void MovePlayerOne(glm::vec3 _NewPos)
{
	GameManager::GetInstance()->CurrentSceneClass()->MovePlayerOne(_NewPos);
}
