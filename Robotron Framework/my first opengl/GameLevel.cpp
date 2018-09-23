#include "GameLevel.h"




GameLevel::GameLevel()
{
}


GameLevel::~GameLevel()
{

}

void GameLevel::Init()
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

	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	SpriteShader = shaderloader.CreateProgram("Shaders/Sprite.vs", "Shaders/Sprite.fs");
	//UISpriteShader = shaderloader.CreateProgram("Shaders/UISprite.vs", "Shaders/UISprite.fs");
	//TextShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");

	MySkybox = new CubeMap(MyCamera, SkyboxShader, "Space/bkg1_top.png", "Space/bkg1_bot.png", "Space/bkg1_right.png", "Space/bkg1_left.png", "Space/bkg1_front.png", "Space/bkg1_back.png");

	Arena = new Sprite("Textures/Arena.png", MyCamera, SpriteShader);
	Arena->AddScale(glm::vec3(2, 2, 0.0f));
	Arena->SetTranslation(glm::vec3(0.0f, -0.5f, 0.0f));

	Balls[0]->Init("Textures/Balls/Player1/Ball.png", MyCamera, SpriteShader, XBoxControllers[0]);
	Balls[0]->ChangePosition({ -0.5, 0.0 });
	Balls[1]->Init("Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader, XBoxControllers[1]);
	Balls[1]->ChangePosition({ -0.5, -1.0 });
	Balls[2]->Init("Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader, XBoxControllers[2]);
	Balls[2]->ChangePosition({ 0.5, -1.0 });
	Balls[3]->Init("Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader, XBoxControllers[3]);
	Balls[3]->ChangePosition({ 0.5, 0.0 });
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
		if (Ball->DeadY) {
			Ball->render();
		}
	}

	Arena->render();

	for (auto Ball : Balls) {
		if (!Ball->DeadY) {
			Ball->render();
		}
	}
}

void GameLevel::Update()
{
	int alive = 0;
	for (auto Ball : Balls) {
		if (!Ball->Dead) {
			alive++;
		}
	}

	if (alive > 1) {

		for (auto &Target : Balls) {
			for (auto &Ball : Balls) {
				if (Ball != Target && !Ball->Dead && !Target->Dead) {
					if (CheckCollision(Ball, Target)) {

						CollidingPairs.push_back({ Ball, Target });

						float fDistance = sqrtf((Ball->Xpos - Target->Xpos) * (Ball->Xpos - Target->Xpos) + (Ball->Ypos - Target->Ypos) * (Ball->Ypos - Target->Ypos));
						float fOverlap = 0.5f * (fDistance - Ball->ColisionRadius - Target->ColisionRadius);

						Ball->Xpos -= fOverlap * (Ball->Xpos - Target->Xpos) / fDistance;
						Ball->Ypos -= fOverlap * (Ball->Ypos - Target->Ypos) / fDistance;

						Target->Xpos += fOverlap * (Ball->Xpos - Target->Xpos) / fDistance;
						Target->Ypos += fOverlap * (Ball->Ypos - Target->Ypos) / fDistance;
					}
				}
			}
		}

		for (auto c : CollidingPairs) {
			BallPlayer* B1 = c.first;
			BallPlayer* B2 = c.second;

			float fDistance = sqrtf((c.first->Xpos - c.second->Xpos) * (c.first->Xpos - c.second->Xpos) + (c.first->Ypos - c.second->Ypos) * (c.first->Ypos - c.second->Ypos));

			float NX = (c.second->Xpos - c.first->Xpos) / fDistance;
			float NY = (c.second->Ypos - c.first->Ypos) / fDistance;

			float TX = -NY;
			float TY = NX;

			float dpTan1 = B1->SpeedX * TX + B1->SpeedY * TY;
			float dpTan2 = B2->SpeedX * TX + B2->SpeedY * TY;

			float dpNorm1 = B1->SpeedX * NX + B1->SpeedY * NY;
			float dpNorm2 = B2->SpeedX * NX + B2->SpeedY * NY;

			float M1 = (dpNorm1 * (B1->mass - B2->mass) + 2.0f * B2->mass * dpNorm2) / (B1->mass + B2->mass);
			float M2 = (dpNorm2 * (B2->mass - B1->mass) + 2.0f * B1->mass * dpNorm1) / (B1->mass + B2->mass);

			B1->SpeedX = TX * dpTan1 + NX * M1;
			B1->SpeedY = TY * dpTan1 + NY * M1;
			B2->SpeedX = TX * dpTan2 + NX * M2;
			B2->SpeedY = TY * dpTan2 + NY * M2;
		}
		for (int I = 0; I < CollidingPairs.size(); I++) {
			CollidingPairs.pop_back();
		}

		EllipseCollisionTest ArenaCollision(10);

		for (auto Ball : Balls) {
			if (!Ball->Dead) {
				if (!ArenaCollision.collide(ArenaX, ArenaY, ArenaH, ArenaW, Ball->Xpos, Ball->Ypos, Ball->ColisionRadius)) {
					Ball->Dead = true;
					if (Ball->Ypos > -0.5) {
						Ball->DeadY = true;
					}
				}
			}
		}


		for (auto Ball : Balls) {
			Ball->UpdateCharater();
		}
	}
	else {
		for (auto Ball : Balls) {
			if (!Ball->Dead) {
				Ball->wins++;
				if (Ball->wins == 3) {
					//Ball wins
				}
				else {
					ResetBalls();
				}
			}
		}
	}
}

void GameLevel::MoveCharacter(unsigned char KeyState[255])
{
	Balls[0]->MoveCharacter(KeyState);
	Balls[1]->MoveCharacter(KeyState);
	Balls[2]->MoveCharacter(KeyState);
	Balls[3]->MoveCharacter(KeyState);
}

void GameLevel::SetControlers(std::vector<CXBOXController*> Controllers)
{
	XBoxControllers = Controllers;
}

bool GameLevel::CheckCollision(BallPlayer *one, BallPlayer* two) // AABB - Circle collision
{
	return (one->Xpos - two->Xpos) * (one->Xpos - two->Xpos) + (one->Ypos - two->Ypos) * (one->Ypos - two->Ypos) < (one->ColisionRadius + two->ColisionRadius) * (one->ColisionRadius + two->ColisionRadius);
}

void GameLevel::ResetBalls()
{
	Balls[0]->ChangePosition({ -0.5, 0.5 });
	Balls[1]->ChangePosition({ -0.5, -0.5 });
	Balls[2]->ChangePosition({ 0.5, -0.5 });
	Balls[3]->ChangePosition({ 0.5, 0.5 });

	for (auto Ball : Balls) {
		Ball->Dead = false;
		Ball->DeadY = false;
		Ball->SpeedX = 0;
		Ball->SpeedY = 0;
	}
}
