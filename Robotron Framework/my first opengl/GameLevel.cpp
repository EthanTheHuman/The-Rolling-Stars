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

	if (XBoxControllers[0]->IsConnected())
	{
		Temp = new BallPlayer();
		Balls.push_back(Temp);
	}
	if (XBoxControllers[1]->IsConnected())
	{
		Temp = new BallPlayer();
		Balls.push_back(Temp);
	}
	if (XBoxControllers[2]->IsConnected())
	{
		Temp = new BallPlayer();
		Balls.push_back(Temp);
	}
	if (XBoxControllers[3]->IsConnected())
	{
		Temp = new BallPlayer();
		Balls.push_back(Temp);
	}

	

	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	SpriteShader = shaderloader.CreateProgram("Shaders/Sprite.vs", "Shaders/Sprite.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");
	TextLableShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");

	MySkybox = new CubeMap(MyCamera, SkyboxShader, "Space/bkg1_top.png", "Space/bkg1_bot.png", "Space/bkg1_right.png", "Space/bkg1_left.png", "Space/bkg1_front.png", "Space/bkg1_back.png");

	Arena = new Sprite("Textures/Arena.png", MyCamera, SpriteShader);
	Arena->AddScale(glm::vec3(2, 2, 0));
	Arena->SetTranslation(glm::vec3(0.0f, -0.5f, 0.0f));

	if (XBoxControllers[0]->IsConnected())
	{
		Player1ScoreBar = new Sprite("Textures/Player1ScoreBar.png", MyCamera, SpriteShader);
		Player1ScoreBar->SetScale(glm::vec3(-2, 2, 0));
		ObjectInitialized.push_back(true);		//ObjectInitialized[0]
	}
	else
	{
		ObjectInitialized.push_back(false);
	}
	if (XBoxControllers[1]->IsConnected())
	{
		Player2ScoreBar = new Sprite("Textures/Player2ScoreBar.png", MyCamera, SpriteShader);
		Player2ScoreBar->SetScale(glm::vec3(-2, 2, 0));
		ObjectInitialized.push_back(true);		//ObjectInitialized[1]
	}
	else
	{
		ObjectInitialized.push_back(false);
	}
	if (XBoxControllers[2]->IsConnected())
	{
		Player3ScoreBar = new Sprite("Textures/Player3ScoreBar.png", MyCamera, SpriteShader);
		Player3ScoreBar->SetScale(glm::vec3(-2, 2, 0));
		ObjectInitialized.push_back(true);		//ObjectInitialized[2]
	}
	else
	{
		ObjectInitialized.push_back(false);
	}
	if (XBoxControllers[3]->IsConnected())
	{
		Player4ScoreBar = new Sprite("Textures/Player4ScoreBar.png", MyCamera, SpriteShader);
		Player4ScoreBar->SetScale(glm::vec3(-2, 2, 0));
		ObjectInitialized.push_back(true);		//ObjectInitialized[3]
	}
	else
	{
		ObjectInitialized.push_back(false);
	}





	if (XBoxControllers[0]->IsConnected())
	{
		Balls[0]->Init("Textures/Balls/Player1/Ball.png", MyCamera, SpriteShader, XBoxControllers[0]);
		Balls[0]->ChangePosition({ 0.5, 0.0 });
		ObjectInitialized.push_back(true);		//ObjectInitialized[4]
	}

	else
	{
		ObjectInitialized.push_back(false);
	}

	if (XBoxControllers[1]->IsConnected())
	{
		Balls[1]->Init("Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader, XBoxControllers[1]);
		Balls[1]->ChangePosition({ -0.5, -0.0 });
		ObjectInitialized.push_back(true);		//ObjectInitialized[5]
	}

	else
	{
		ObjectInitialized.push_back(false);
	}
	
	if (XBoxControllers[2]->IsConnected())
	{
		Balls[2]->Init("Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader, XBoxControllers[2]);
		Balls[2]->ChangePosition({ 0.5, -1.0 });
		ObjectInitialized.push_back(true);		//ObjectInitialized[6]
	}

	else
	{
		ObjectInitialized.push_back(false);
	}

	if (XBoxControllers[3]->IsConnected())
	{
		Balls[3]->Init("Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader, XBoxControllers[3]);
		Balls[3]->ChangePosition({ -0.5, -1.0 });
		ObjectInitialized.push_back(true);		//ObjectInitialized[7]
	}
	
	else
	{
		ObjectInitialized.push_back(false);
	}

	Player1 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(78.0f, 505.0f), TextLableShader);
	Player2 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(697.0f, 505.0f), TextLableShader);
	Player3 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(78.0, 410.0f), TextLableShader);
	Player4 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(697.0f, 410.0f), TextLableShader);

	Player1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Player2->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Player3->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Player4->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
}

void GameLevel::Deconstruct()
{
	delete MyCamera;
	for (int i = 0; i < Balls.size(); i++) {
		delete Balls[i];
	}
	Balls.clear();
	delete Arena;
	delete MySkybox;
	nextScene = NOTHING;
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

	//ScoreBoard Render

	if (ObjectInitialized[0] == true)
	{
		Player1ScoreBar->render();
	}
	if (ObjectInitialized[1] == true)
	{
		Player2ScoreBar->render();
	}
	if (ObjectInitialized[2] == true)
	{
		Player3ScoreBar->render();
	}
	if (ObjectInitialized[3] == true)
	{
		Player4ScoreBar->render();
	}

	//Player Render

	if (ObjectInitialized[4] == true)
	{
		Player1->Render();
	}
	if (ObjectInitialized[5] == true)
	{
		Player2->Render();
	}
	if (ObjectInitialized[6] == true)
	{
		Player3->Render();
	}
	if (ObjectInitialized[7] == true)
	{
		Player4->Render();
	}

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

						//Play sound
						Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->bounce, 0, false, &Sound::GetInstance()->fxchannel);

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
				if (!ArenaCollision.collide(ArenaX, ArenaY, ArenaH, ArenaW, Ball->Xpos, Ball->Ypos, 0.01)) {

					//Play falling sound
					Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->fxSplat, 0, false, &Sound::GetInstance()->fxchannel);

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
				float scale = 0.1 + (Ball->wins * 0.2);
				Ball->SetScale({ scale,scale,scale });
				Ball->ColisionRadius = scale;

				if (Ball->wins == 3) {
					nextScene = TOMAIN;
				}
			}
		}
		ResetBalls();
	}

	std::ostringstream P1iConvert;
	std::ostringstream P2iConvert;
	std::ostringstream P3iConvert;
	std::ostringstream P4iConvert;

	if (XBoxControllers[0]->IsConnected())
	{
		P1iConvert << Balls[0]->wins;
		Player1->SetText(P1iConvert.str());
	}
	if (XBoxControllers[1]->IsConnected())
	{
		P2iConvert << Balls[1]->wins;
		Player2->SetText(P2iConvert.str());
	}
	if (XBoxControllers[2]->IsConnected())
	{
		P3iConvert << Balls[2]->wins;
		Player3->SetText(P3iConvert.str());
	}
	if (XBoxControllers[3]->IsConnected())
	{
		P4iConvert << Balls[3]->wins;
		Player4->SetText(P4iConvert.str());
	}
}

void GameLevel::MoveCharacter(unsigned char KeyState[255])
{
	if (ObjectInitialized[0] == true)
	{
		Balls[0]->MoveCharacter(KeyState);
	}
	if (ObjectInitialized[1] == true)
	{
		Balls[1]->MoveCharacter(KeyState);
	}
	if (ObjectInitialized[2] == true)
	{
		Balls[2]->MoveCharacter(KeyState);
	}
	if (ObjectInitialized[3] == true)
	{
		Balls[3]->MoveCharacter(KeyState);
	}

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
	if (ObjectInitialized[0] == true)
	{
		Balls[0]->ChangePosition({ 0.5, 0.0 });
	}
	if (ObjectInitialized[1] == true)
	{
		Balls[1]->ChangePosition({ -0.5, -0.0 });
	}
	if (ObjectInitialized[2] == true)
	{
		Balls[2]->ChangePosition({ 0.5, -1.0 });
	}
	if (ObjectInitialized[3] == true)
	{
		Balls[3]->ChangePosition({ -0.5, -1.0 });
	}

	for (auto Ball : Balls) {
		Ball->Dead = false;
		Ball->DeadY = false;
		Ball->SpeedX = 0;
		Ball->SpeedY = 0;
	}
}
