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

	Title = new UISprite("Textures/TheLogo.png", MyCamera, UISpriteShader);
	Title->SetScale({ 0.6, 0.6, 0.0 });
	Title->SetTranslation({ 0, 0.5, 0 });

	/*Controls = new UISprite("Textures/Controls.png", MyCamera, UISpriteShader);
	Controls->SetScale({ 1, 1, 1 });
	Controls->SetTranslation({ 0, 0, 0 });*/

	//Play Button
	TempLable = new TextLabel("PLAY", "Fonts/arial.ttf", glm::vec2(332, 300));
	mainMenu.push_back(TempLable);

	//Exit Button
	TempLable = new TextLabel("Exit", "Fonts/arial.ttf", glm::vec2(350, 200));
	mainMenu.push_back(TempLable);

	//Player connected messages
	Player1 = new TextLabel("Player 1", "Fonts/arial.ttf", glm::vec2(0, 10));
	Player1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

	Player2 = new TextLabel("Player 2", "Fonts/arial.ttf", glm::vec2(620, 10));
	Player2->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

	Player3 = new TextLabel("Player 3", "Fonts/arial.ttf", glm::vec2(0, 560));
	Player3->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));

	Player4 = new TextLabel("Player 4", "Fonts/arial.ttf", glm::vec2(620, 560));
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
	for (int i = 0; i < playMenu.size(); i++) {
		delete playMenu[i];
	}
	playMenu.clear();
	for (int i = 0; i < coopMenu.size(); i++) {
		delete coopMenu[i];
	}
	coopMenu.clear();
	delete _Player;
	delete MySkybox;
	nextScene = NOTHING;
	menu = MAIN;
	selection = 0;
}

void MainMenu::Render()
{
	MyCamera->Update();
	glFrontFace(GL_CCW);

	//Background
	MySkybox->Render();
	Title->render();

	//Textlable
	for (int i = 0; i < mainMenu.size(); i++)
	{
		mainMenu[i]->Render();
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
