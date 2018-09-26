#include "MainMenu.h"

//pointers
GameManager* m_pGameManager = GameManager::GetInstance();


MainMenu::MainMenu()
{
}

void MainMenu::Init()
{
	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	UISpriteShader = shaderloader.CreateProgram("Shaders/UISprite.vs", "Shaders/UISprite.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");
	TextLableShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");

	Title = new UISprite("Textures/TheLogo.png", MyCamera, UISpriteShader);
	Title->SetScale({ 0.9, 0.9, 0.0 });
	Title->SetTranslation({ 0, 0.5, 0 });

	Dpad = new UISprite("Textures/Dpad.png", MyCamera, UISpriteShader);
	Dpad->SetScale({ 0.2, 0.2, 0.0 });
	Dpad->SetTranslation({ 0, -0.23, 0 });

	/*Controls = new UISprite("Textures/Controls.png", MyCamera, UISpriteShader);
	Controls->SetScale({ 1, 1, 1 });
	Controls->SetTranslation({ 0, 0, 0 });*/

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
	Player1 = new TextLabel("Player 1", "Fonts/arial.ttf", glm::vec2(0, 10), TextLableShader);
	Player1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

	Player2 = new TextLabel("Player 2", "Fonts/arial.ttf", glm::vec2(620, 10), TextLableShader);
	Player2->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));

	Player3 = new TextLabel("Player 3", "Fonts/arial.ttf", glm::vec2(0, 560), TextLableShader);
	Player3->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

	Player4 = new TextLabel("Player 4", "Fonts/arial.ttf", glm::vec2(620, 560), TextLableShader);
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

	 IsMainMenu = true;
	 IsSettings = false;
	 IsCredits = false;

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
	Title->render();
	Dpad->render();

	//Textlable
	if (IsMainMenu)
	{
		for (int i = 0; i < mainMenu.size(); i++)
		{
			mainMenu[i]->Render();
		}
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

	if (XBoxControllers[0]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_UP)
	{
		//UP
		std::cout << "Dpad Up" << std::endl;
		if (selection == 1)
		{
			selection--;
		}
	}
	if (XBoxControllers[0]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_DOWN)
	{
		//DOWN
		std::cout << "Dpad Down" << std::endl;
		if (selection == 0)
		{
			selection++;
		}
	}
	if (XBoxControllers[0]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)
	{
		//LEFT
		std::cout << "Dpad Left" << std::endl;
	}
	if (XBoxControllers[0]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_RIGHT)
	{
		//RIGHT
		std::cout << "Dpad Right" << std::endl;
	}
	if (XBoxControllers[0]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_A)
	{
		//A
		std::cout << "Gamepad A" << std::endl;
		
		//Play
		if (selection == 0)
		{
			nextScene = NEXT;
				
		}

		//Exit
		if (selection == 1)
		{
			nextScene = EXIT;
		}
	}

	if (selection == 0)
	{
		mainMenu[0]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		mainMenu[1]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (selection == 1)
	{
		mainMenu[1]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		mainMenu[0]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
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
