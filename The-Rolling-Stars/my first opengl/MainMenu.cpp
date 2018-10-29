#include "MainMenu.h"

//pointers
GameManager* m_pGameManager = GameManager::GetInstance();

enum MenuStates
{
	MainMenues = 0,
	Controls,
	Credits
};

MenuStates CurrentState = MainMenues;

MainMenu::MainMenu()
{
}

void MainMenu::Init()
{
	CurrentState = MainMenues;

	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 90, 0), glm::vec3(0, 1, 0));
	UISpriteShader = shaderloader.CreateProgram("Shaders/UISprite.vs", "Shaders/UISprite.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");
	TextLableShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");

	Title = new UISprite("Textures/TheLogo.png", MyCamera, UISpriteShader);
	Title->SetScale({ 0.9, 0.9, 0.0 });
	Title->SetTranslation({ 0, 0.5, 0 });

	Dpad = new UISprite("Textures/Dpad.png", MyCamera, UISpriteShader);
	Dpad->SetScale({ 0.2, 0.2, 0.0 });
	Dpad->SetTranslation({ 0, -0.23, 0 });

	Back = new UISprite("Textures/back.png", MyCamera, UISpriteShader);
	Back->SetScale({ 0.25, 0.25, 0.0 });
	Back->SetTranslation({ 0.1, -0.88, 0 });

	controlsScene= new UISprite("Textures/Controls.png", MyCamera, UISpriteShader);
	controlsScene->SetScale({ 1, 1.3, 0 });
	controlsScene->SetTranslation({ 0, 0.115, 0 });

	creditsScene = new UISprite("Textures/Credits.png", MyCamera, UISpriteShader);
	creditsScene->SetScale({ 1, 1, 0.0 });
	creditsScene->SetTranslation({ 0, 0, 0 });

	Sound::GetInstance()->Musicchannel->stop();
	Sound::GetInstance()->fxchannel->stop();
	Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->menuTheme, 0, false, &Sound::GetInstance()->Musicchannel);

	//Play Button
	TextLabel * TempLable;
	TempLable = new TextLabel("PLAY", "Fonts/arial.ttf", glm::vec2(342, 300), TextLableShader);
	mainMenu.push_back(TempLable);

	//Exit Button
	TempLable = new TextLabel("EXIT", "Fonts/arial.ttf", glm::vec2(345, 135), TextLableShader);
	mainMenu.push_back(TempLable);

	//Controls Button
	TempLable = new TextLabel("CONTROLS", "Fonts/arial.ttf", glm::vec2(60, 215), TextLableShader);
	mainMenu.push_back(TempLable);

	//Credits Button
	TempLable = new TextLabel("CREDITS", "Fonts/arial.ttf", glm::vec2(470, 215), TextLableShader);
	mainMenu.push_back(TempLable);



	//Player connected messages
	Player1 = new TextLabel("Player 1", "Fonts/arial.ttf", glm::vec2(0, 560), TextLableShader);
	Player1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

	Player2 = new TextLabel("Player 2", "Fonts/arial.ttf", glm::vec2(620, 560), TextLableShader);
	Player2->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));

	Player3 = new TextLabel("Player 3", "Fonts/arial.ttf", glm::vec2(0, 10), TextLableShader);
	Player3->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

	Player4 = new TextLabel("Player 4", "Fonts/arial.ttf", glm::vec2(620, 10), TextLableShader);
	Player4->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));

	MySkybox = new CubeMap(MyCamera, SkyboxShader, "Space/bkg1_top.png", "Space/bkg1_bot.png", "Space/bkg1_right.png", "Space/bkg1_left.png", "Space/bkg1_front.png", "Space/bkg1_back.png");
	
}

void MainMenu::Deconstruct()
{
	delete MyCamera;
	for (int i = 0; i < mainMenu.size(); i++) {
		delete mainMenu[i];
	}
	mainMenu.clear();
	for (int i = 0; i < controls.size(); i++) {
		delete controls[i];
	}
	controls.clear();
	for (int i = 0; i < credits.size(); i++) {
		delete credits[i];
	}
	credits.clear();
	delete MySkybox;
	nextScene = NOTHING;
	menu = MAIN;
	selection = 0;

	CurrentState = MainMenues;

	delete Player1;
	delete Player2;
	delete Player3;
	delete Player4;

	delete Title;
}

void MainMenu::Render()
{
	MyCamera->Update();
	glFrontFace(GL_CCW);

	//Background
	MySkybox->Render();


	//Textlable
	if (CurrentState == MainMenues)
	{
		Title->render();
		Dpad->render();
		for (int i = 0; i < mainMenu.size(); i++)
		{
			mainMenu[i]->Render();
		}
	}
	else if (CurrentState == Controls)
	{
		//Render Controls
		controlsScene->render();
		Back->render();
	}
	else
	{
		// Render Credits
		creditsScene->render();
		Back->render();
	}


	

	if (XBoxControllers[0]->IsConnected())
	{
		Player1->Render();
	}
	if (XBoxControllers[1]->IsConnected())
	{
		Player2->Render();
	}
	if (XBoxControllers[2]->IsConnected())
	{
		Player3->Render();
	}
	if (XBoxControllers[3]->IsConnected())
	{
		Player4->Render();
	}

}


void MainMenu::Update()
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.00005f;

	GLfloat radius = 5.0f;
	GLfloat camX = sin(currentTime) * radius;
	GLfloat camZ = cos(currentTime) * radius;
	MyCamera->SetCameraPosition({ camX, 2.5, camZ });

	if (GetFirstConnectedConrtoller()->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_UP)
	{
		Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->select, 0, false, &Sound::GetInstance()->fxchannel);
		//UP
		if (CurrentState == MainMenues)
		{
			std::cout << "Dpad Up" << std::endl;
			//0
			selection = 0;
		}
		else if (CurrentState == Controls)
		{
			// Controls command for up
			selection = NULL;
		}
		else
		{
			// Credits command for up
			selection = NULL;
		}
	}
	if (GetFirstConnectedConrtoller()->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN)
	{
		Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->select, 0, false, &Sound::GetInstance()->fxchannel);
		//DOWN
		if (CurrentState == MainMenues)
		{
			std::cout << "Dpad Down" << std::endl;
			//1
			selection = 1;
		}
		else if (CurrentState == Controls)
		{
			// Controls command for down
			selection = NULL;
		}
		else
		{
			// Credits command for down
			selection = NULL;
		}
	}
	if (GetFirstConnectedConrtoller()->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)
	{
		Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->select, 0, false, &Sound::GetInstance()->fxchannel);
		//LEFT
		if (CurrentState == MainMenues)
		{
			std::cout << "Dpad Left" << std::endl;
			//2
			selection = 2;
		}
		else if (CurrentState == Controls)
		{
			// Controls command for left
			selection = NULL;
		}
		else
		{
			// Credits command for left
			selection = NULL;
		}
	}
	if (GetFirstConnectedConrtoller()->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->select, 0, false, &Sound::GetInstance()->fxchannel);
		//RIGHT
		if (CurrentState == MainMenues)
		{
			std::cout << "Dpad Right" << std::endl;
			//3
			selection = 3;
		}
		else if (CurrentState == Controls)
		{
			// Controls command for right
			selection = NULL;
		}
		else
		{
			// Credits command for right
			selection = NULL;
		}
	}
	if (GetFirstConnectedConrtoller()->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_A)
	{
		//A
		std::cout << "Gamepad A" << std::endl;
		Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->select, 0, false, &Sound::GetInstance()->fxchannel);
		
		if (CurrentState == MainMenues)
		{
			//Play
			if (selection == 0 && TwoPlayersConnected())
			{
				nextScene = NEXT;

			}
			else
			{
				std::cout << "Two Players must be Connected" << std::endl;
			}

			//Exit
			if (selection == 1)
			{
				nextScene = EXIT;
			}

			if (selection == 2)
			{
				CurrentState = Controls;
			}

			if (selection == 3)
			{
				CurrentState = Credits;
			}
		}
	}

	if (GetFirstConnectedConrtoller()->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_B)
	{
		if (CurrentState == Controls)
		{
			// Controls command for B
			CurrentState = MainMenues;
		}
		else
		{
			// Credits command for B
			CurrentState = MainMenues;
		}
	}

	if (selection == 0)
	{
		mainMenu[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		mainMenu[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[3]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (selection == 1)
	{
		mainMenu[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[1]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		mainMenu[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[3]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (selection == 2)
	{
		mainMenu[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[2]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		mainMenu[3]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (selection == 3)
	{
		mainMenu[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[2]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
		mainMenu[3]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	}
}

MainMenu::~MainMenu()
{

}

void MainMenu::MoveCharacter(unsigned char KeyState[255]) {
	if (KeyState[(unsigned char)'a'] == INPUT_FIRST_PRESS)
	{

	}
	if (KeyState[(unsigned char)'d'] == INPUT_FIRST_PRESS)
	{

	}
	if (KeyState[(unsigned char)' '] == INPUT_FIRST_PRESS)
	{

	}
	if (KeyState[(unsigned char)'\x1b'] == INPUT_FIRST_PRESS)
	{

	}
	if (KeyState[(unsigned char)'w'] == INPUT_FIRST_PRESS)
	{

	}
	if (KeyState[(unsigned char)'s'] == INPUT_FIRST_PRESS)
	{

	}
}

void MainMenu::SetControlers(std::vector<CXBOXController*> Controllers)
{
	XBoxControllers = Controllers;
}

bool MainMenu::TwoPlayersConnected() {

	if (XBoxControllers[0]->IsConnected() && XBoxControllers[1]->IsConnected())
	{
		return true;
	}
	if (XBoxControllers[0]->IsConnected() && XBoxControllers[2]->IsConnected())
	{
		return true;
	}
	if (XBoxControllers[0]->IsConnected() && XBoxControllers[3]->IsConnected())
	{
		return true;
	}
	if (XBoxControllers[1]->IsConnected() && XBoxControllers[2]->IsConnected())
	{
		return true;
	}
	if (XBoxControllers[1]->IsConnected() && XBoxControllers[3]->IsConnected())
	{
		return true;
	}
	if (XBoxControllers[2]->IsConnected() && XBoxControllers[3]->IsConnected())
	{
		return true;
	}


	return false;

}

CXBOXController* MainMenu::GetFirstConnectedConrtoller()
{
	if (XBoxControllers[0]->IsConnected())
	{
		return XBoxControllers[0];
	}
	if (XBoxControllers[0]->IsConnected() == false && XBoxControllers[1]->IsConnected())
	{
		return XBoxControllers[1];
	}
	if (XBoxControllers[0]->IsConnected() == false && XBoxControllers[1]->IsConnected() == false && XBoxControllers[2]->IsConnected())
	{
		return XBoxControllers[2];

	}
	if (XBoxControllers[0]->IsConnected() == false && XBoxControllers[1]->IsConnected() == false && XBoxControllers[2]->IsConnected() == false && XBoxControllers[3]->IsConnected())
	{
		return XBoxControllers[3];

	}

	else
	{
		return  XBoxControllers[0];
	}
}
