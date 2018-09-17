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
#include "CubeMap.h"
#include "dependencies\FMOD\fmod.hpp"
#include "CXBOXController.h"

//Library Includes
#include <Windows.h>
#include <cassert>
//#include <vld.h>
#include <thread>




// Namespace
using namespace std;

// Functions
void init();
void render();

void Keyboard_Down(unsigned char key, int x, int y);
void Keyboard_Up(unsigned char key, int x, int y);
void KeyboardUpdate();

void update();

//Global Var
Camera * MyCamera;
Model * MyPyramid;
Sprite * KarateGuy1;
Sprite * KarateGuy2;

TextLabel * label;

CubeMap * MySkybox;

unsigned char KeyState[255]; // Global

char* _pcPacketData = 0; //A local buffer to receive packet data info

// Main function
int main(int argc, char **argv)
{
	// OpenGL Window Creation
	glutInit(&argc, argv);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 200);
	glutInitWindowSize(SRCWIDTH, SRCHEIGHT);
	glutCreateWindow("The Rolling Stars");

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