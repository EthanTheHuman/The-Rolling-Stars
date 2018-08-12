#include "MainMenu.h"

MainMenu::MainMenu()
{
}

void MainMenu::Init()
{
	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	SpriteShader = shaderloader.CreateProgram("Shaders/Sprite.vs", "Shaders/Sprite.fs");
	UISpriteShader = shaderloader.CreateProgram("Shaders/UISprite.vs", "Shaders/UISprite.fs");
	ModelBasicShader = shaderloader.CreateProgram("Shaders/ModelBasic.vs", "Shaders/ModelBasic.fs");
	AmbientShader = shaderloader.CreateProgram("Shaders/Ambient.vs", "Shaders/Ambient.fs");
	TextShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");

	Title = new UISprite("Textures/Cubemap/Title.png", MyCamera, UISpriteShader);
	Title->SetScale({ 0.3, 0.3, 0.3 });
	Title->SetTranslation({ 0, 0.5, 0 });

	Controls = new UISprite("Textures/Controls.png", MyCamera, UISpriteShader);
	Controls->SetScale({ 1, 1, 1 });
	Controls->SetTranslation({ 0, 0, 0 });

	_Player = new Player(MyCamera, AmbientShader);
	MySkybox = new CubeMap(MyCamera, SkyboxShader, "Space/bkg1_top.png", "Space/bkg1_bot.png", "Space/bkg1_right.png", "Space/bkg1_left.png", "Space/bkg1_front.png", "Space/bkg1_back.png");
	MenuUpdate();
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
	_Player->Render();

}


void MainMenu::Update()
{
	float currentTime = glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.00005f;

	GLfloat radius = 5.0f;
	GLfloat camX = sin(currentTime) * radius;
	GLfloat camZ = cos(currentTime) * radius;
	MyCamera->SetCameraPosition({ camX, 2.5, camZ });
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