#include "GameLevel.h"




GameLevel::GameLevel()
{
	BallPlayer* Temp;
	Temp = new BallPlayer();
	Balls.push_back(Temp);
	Temp = new BallPlayer();
	Balls.push_back(Temp);
	Temp = new BallPlayer();
	Balls.push_back(Temp);
	Temp = new BallPlayer();
	Balls.push_back(Temp);
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

	Balls[0]->Init("Textures/Balls/Player1/Ball.png", MyCamera, SpriteShader);
	Balls[0]->ChangePosition({ -1,1 });
	Balls[1]->Init("Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader);
	Balls[1]->ChangePosition({ -1,-1 });
	Balls[2]->Init("Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader);
	Balls[2]->ChangePosition({ 1,-1 });
	Balls[3]->Init("Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader);
	Balls[3]->ChangePosition({ 1,1 });
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
	for (auto Ball : Balls) {
		Ball->render();
	}
}

void GameLevel::Update()
{
	for (auto &Target : Balls) {
		for (auto &Ball : Balls) {
			if (Ball != Target) {
				if (CheckCollision(Ball, Target)) {
					float BX = Ball->ReturnPosition().x;
					float BY = Ball->ReturnPosition().y;
					float TX = Target->ReturnPosition().x;
					float TY = Target->ReturnPosition().y;

					float fDistance = sqrtf((BX - TX) * (BX - TX) + (BY - TY) * (BY - TY));
					float fOverlap = 0.5f * (fDistance - Ball->ColisionRadius - Target->ColisionRadius);

					BX -= fOverlap * (BX - TX) / fDistance;
					BY -= fOverlap * (BY - TY) / fDistance;

					TX += fOverlap * (BX - TX) / fDistance;
					TY += fOverlap * (BY - TY) / fDistance;

					Ball->ChangePosition({ BX, BY });
					Target->ChangePosition({ TX, TY });
				}
			}
		}
	}
	for (auto Ball : Balls) {
		Ball->UpdateCharater();
	}
}

void GameLevel::MoveCharacter(unsigned char KeyState[255])
{
	Balls[0]->MoveCharacter(KeyState);
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