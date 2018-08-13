#include "GameLevel.h"




GameLevel::GameLevel()
{
	Player1 = new BallPlayer();
	Player2 = new BallPlayer();
	Player3 = new BallPlayer();
	Player4 = new BallPlayer();
}


GameLevel::~GameLevel()
{

}

void GameLevel::Init()
{
	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	SpriteShader = shaderloader.CreateProgram("Shaders/Sprite.vs", "Shaders/Sprite.fs");
	UISpriteShader = shaderloader.CreateProgram("Shaders/UISprite.vs", "Shaders/UISprite.fs");
	TextShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");

	Player1->Init("Textures/Balls/Player1/Ball.png", MyCamera, SpriteShader);
	Player2->Init("Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader);
	Player2->ChangePosition({ 1,1 });
	Player3->Init("Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader);
	Player4->Init("Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader);
	MySkybox = new CubeMap(MyCamera, SkyboxShader, "Space/bkg1_top.png", "Space/bkg1_bot.png", "Space/bkg1_right.png", "Space/bkg1_left.png", "Space/bkg1_front.png", "Space/bkg1_back.png");
}

void GameLevel::Deconstruct()
{

}

void GameLevel::Render()
{
	MyCamera->Update();
	glFrontFace(GL_CCW);

	MySkybox->Render();
	if (!CheckCollision(Player1, Player2)) {
		Player1->render();
		Player2->render();
	}
	//Player3->render();
	//Player4->render();
}

void GameLevel::Update()
{
	Player1->UpdateCharater();
	Player2->UpdateCharater();
}

void GameLevel::MoveCharacter(unsigned char KeyState[255])
{
	Player1->MoveCharacter(KeyState);
}

bool GameLevel::CheckCollision(BallPlayer *one, BallPlayer* two) // AABB - Circle collision
{
	float x1 = one->ReturnPosition().x;
	float y1 = one->ReturnPosition().y;
	float r1 = one->ColisionRadius;
	float x2 = two->ReturnPosition().x;
	float y2 = two->ReturnPosition().y;
	float r2 = two->ColisionRadius;
	return fabs((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < (r1 + r2) * (r1 + r2);
}