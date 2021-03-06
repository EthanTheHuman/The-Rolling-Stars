#include "GameLevel.h"

float CurrentTime = 0.0f;
float LastExacuted = 0.0f;
float ElapsedTime = CurrentTime - LastExacuted;

float Delay = 0.0f;
float DelayTemp;
bool IsBouncy = false;

bool IsDelayed = false;
bool IsColiding = false;
bool bPlayer1Wins, bPlayer2Wins, bPlayer3Wins, bPlayer4Wins = false;
bool bOverallPlayer1Wins, bOverallPlayer2Wins, bOverallPlayer3Wins, bOverallPlayer4Wins = false;



GameLevel::GameLevel()
{

}


GameLevel::~GameLevel()
{

}

void GameLevel::Init()
{
	CurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
	//LastExacuted = glutGet(GLUT_ELAPSED_TIME) / 1000;

	BallPlayer* Temp;

		Temp = new BallPlayer();
		Balls.push_back(Temp);

		Temp = new BallPlayer();
		Balls.push_back(Temp);

		Temp = new BallPlayer();
		Balls.push_back(Temp);

		Temp = new BallPlayer();
		Balls.push_back(Temp);

	Sound::GetInstance()->Musicchannel->stop();
	Sound::GetInstance()->fxchannel->stop();
	Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->bgmTheme, 0, false, &Sound::GetInstance()->Musicchannel);

	MyCamera = new Camera(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	SpriteShader = shaderloader.CreateProgram("Shaders/Sprite.vs", "Shaders/Sprite.fs");
	SkyboxShader = shaderloader.CreateProgram("Shaders/Cubemap.vs", "Shaders/Cubemap.fs");
	TextLableShader = shaderloader.CreateProgram("Shaders/Text.vs", "Shaders/Text.fs");

	MySkybox = new CubeMap(MyCamera, SkyboxShader, "Space/bkg1_top.png", "Space/bkg1_bot.png", "Space/bkg1_right.png", "Space/bkg1_left.png", "Space/bkg1_front.png", "Space/bkg1_back.png");

	Arena = new Sprite("Textures/Arena.png", MyCamera, SpriteShader);
	Arena->AddScale(glm::vec3(2, 2, 0));
	Arena->SetTranslation(glm::vec3(0.0f, -0.5f, 0.0f));

	Player1Wins = new Sprite("Textures/P1.png", MyCamera, SpriteShader);
	Player1Wins->AddScale(glm::vec3(-2, 2, 0));
	Player1Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	Player2Wins = new Sprite("Textures/P2.png", MyCamera, SpriteShader);
	Player2Wins->AddScale(glm::vec3(-2, 2, 0));
	Player2Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	Player3Wins = new Sprite("Textures/P3.png", MyCamera, SpriteShader);
	Player3Wins->AddScale(glm::vec3(-2, 2, 0));
	Player3Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	Player4Wins = new Sprite("Textures/P4.png", MyCamera, SpriteShader);
	Player4Wins->AddScale(glm::vec3(-2, 2, 0));
	Player4Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	OverallPlayer1Wins = new Sprite("Textures/Player1.png", MyCamera, SpriteShader);
	OverallPlayer1Wins->AddScale(glm::vec3(-2, 2, 0));
	OverallPlayer1Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	OverallPlayer2Wins = new Sprite("Textures/Player2.png", MyCamera, SpriteShader);
	OverallPlayer2Wins->AddScale(glm::vec3(-2, 2, 0));
	OverallPlayer2Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	OverallPlayer3Wins = new Sprite("Textures/Player3.png", MyCamera, SpriteShader);
	OverallPlayer3Wins->AddScale(glm::vec3(-2, 2, 0));
	OverallPlayer3Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

	OverallPlayer4Wins = new Sprite("Textures/Player4.png", MyCamera, SpriteShader);
	OverallPlayer4Wins->AddScale(glm::vec3(-2, 2, 0));
	OverallPlayer4Wins->SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f));

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
		Balls[0]->AddScale(glm::vec3(NewBallScale, NewBallScale, NewBallScale));
		Balls[0]->ColisionRadius = Balls[0]->ColisionRadius * NewBallScale;
		ObjectInitialized.push_back(true);		//ObjectInitialized[4]
	}

	else
	{
		ObjectInitialized.push_back(false);
		Balls[0]->Dead = true;
	}

	if (XBoxControllers[1]->IsConnected())
	{
		Balls[1]->Init("Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader, XBoxControllers[1]);
		Balls[1]->ChangePosition({ -0.5, -0.0 });
		Balls[1]->AddScale(glm::vec3(NewBallScale, NewBallScale, NewBallScale));
		Balls[1]->ColisionRadius = Balls[1]->ColisionRadius * NewBallScale;
		ObjectInitialized.push_back(true);		//ObjectInitialized[5]
	}

	else
	{
		ObjectInitialized.push_back(false);
		Balls[1]->Dead = true;
	}

	if (XBoxControllers[2]->IsConnected())
	{
		Balls[2]->Init("Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader, XBoxControllers[2]);
		Balls[2]->ChangePosition({ 0.5, -1.0 });
		Balls[2]->AddScale(glm::vec3(NewBallScale, NewBallScale, NewBallScale));
		Balls[2]->ColisionRadius = Balls[2]->ColisionRadius * NewBallScale;
		ObjectInitialized.push_back(true);		//ObjectInitialized[6]
	}

	else
	{
		ObjectInitialized.push_back(false);
		Balls[2]->Dead = true;
	}

	if (XBoxControllers[3]->IsConnected())
	{
		Balls[3]->Init("Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader, XBoxControllers[3]);
		Balls[3]->ChangePosition({ -0.5, -1.0 });
		Balls[3]->AddScale(glm::vec3(NewBallScale, NewBallScale, NewBallScale));
		Balls[3]->ColisionRadius = Balls[3]->ColisionRadius * NewBallScale;
		ObjectInitialized.push_back(true);		//ObjectInitialized[7]
	}

	else
	{
		ObjectInitialized.push_back(false);
		Balls[3]->Dead = true;
	}

	Player1 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(78.0f, 505.0f), TextLableShader);
	Player2 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(697.0f, 505.0f), TextLableShader);
	Player3 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(78.0, 410.0f), TextLableShader);
	Player4 = new TextLabel("0", "Fonts/arial.ttf", glm::vec2(697.0f, 410.0f), TextLableShader);

	Player1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Player2->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Player3->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	Player4->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));

}

void GameLevel::Deconstruct()
{
	delete MyCamera;
	for (int i = 0; i < Balls.size(); i++) {
		delete Balls[i];
	}
	Balls.clear();
	delete Arena;
	if (ObjectInitialized[0]) {
		delete Player1ScoreBar;

	}
	if (ObjectInitialized[1]) {
		delete Player2ScoreBar;

	}
	if (ObjectInitialized[2]) {
		delete Player3ScoreBar;

	}
	if (ObjectInitialized[3]) {
		delete Player4ScoreBar;

	}

	delete Player1Wins;
	delete OverallPlayer1Wins;
	delete Player1;
	delete Player2Wins;
	delete OverallPlayer2Wins;
	delete Player2;
	delete Player3Wins;
	delete OverallPlayer3Wins;
	delete Player3;
	delete Player4Wins;
	delete OverallPlayer4Wins;
	delete Player4;

	nextScene = NOTHING;
	ObjectInitialized.clear();
}

void GameLevel::Render()
{
	MyCamera->Update();
	glFrontFace(GL_CCW);

	MySkybox->Render();

	if (ObjectInitialized[0] == true && Balls[0]->DeadY)
	{
		Balls[0]->render();
	}
	if (ObjectInitialized[1] == true && Balls[1]->DeadY)
	{
		Balls[1]->render();
	}
	if (ObjectInitialized[2] == true && Balls[2]->DeadY)
	{
		Balls[2]->render();
	}
	if (ObjectInitialized[3] == true && Balls[3]->DeadY)
	{
		Balls[3]->render();
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

	//Score Text Render

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

	//Player Render
	if (ObjectInitialized[0] == true && !Balls[0]->DeadY)
	{
		Balls[0]->render();
	}
	if (ObjectInitialized[1] == true && !Balls[1]->DeadY)
	{
		Balls[1]->render();
	}
	if (ObjectInitialized[2] == true && !Balls[2]->DeadY)
	{
		Balls[2]->render();
	}
	if (ObjectInitialized[3] == true && !Balls[3]->DeadY)
	{
		Balls[3]->render();
	}

	//Player Win Sprite

	if (bPlayer1Wins)
	{
		Player1Wins->render();
	}
	if (bPlayer2Wins)
	{
		Player2Wins->render();
	}
	if (bPlayer3Wins)
	{
		Player3Wins->render();
	}
	if (bPlayer4Wins)
	{
		Player4Wins->render();
	}

	//overall Win Sprite

	if (bOverallPlayer1Wins)
	{
		OverallPlayer1Wins->render();
	}
	if (bOverallPlayer2Wins)
	{
		OverallPlayer2Wins->render();
	}
	if (bOverallPlayer3Wins)
	{
		OverallPlayer3Wins->render();
	}
	if (bOverallPlayer4Wins)
	{
		OverallPlayer4Wins->render();
	}
	

}

void GameLevel::Update()
{
	CurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000;
	ElapsedTime = CurrentTime - LastExacuted;
	DelayTemp = ElapsedTime;

	if (XBoxControllers[0]->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_Y)
	{
		IsBouncy = true;
	}

	int alive = 0;
	for (auto Ball : Balls) {
		if (!Ball->Dead) {
			alive++;
		}
	}
	if (alive > 1) {

		for (auto Ball : Balls) {
			if (!Ball->Dead)
			{
				Ball->SetScale({ Ball->GetScale() + 0.00003f });
				Ball->ColisionRadius = Ball->GetScale().x + 0.00003f;
			}
		}

		for (auto &Target : Balls) {
			for (auto &Ball : Balls) {
				if (Ball != Target && !Ball->Dead && !Target->Dead) {
					if (CheckCollision(Ball, Target)) {

						//Play sound
						if (IsColiding == false)
						{
							if (IsBouncy)
							{
								Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->bouncey, 0, false, &Sound::GetInstance()->fxchannel);
							}
							else
							{
								Sound::GetInstance()->audioMgr->playSound(Sound::GetInstance()->bounce, 0, false, &Sound::GetInstance()->fxchannel);
							}
							IsColiding = true;
						}
						

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
			IsColiding = false;
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
		if (IsDelayed == false)
		{
			DelayTemp = 0.0f;
			Delay = 3.0f;
			IsDelayed = true;
			LastExacuted = glutGet(GLUT_ELAPSED_TIME) / 1000;

			for (int i = 0; i < Balls.size(); i++)
			{
				if (!Balls[i]->Dead && Balls[i]->wins != 2)
				{
					switch (i)
					{
					case 0: {
						bPlayer1Wins = true;

						break;
					}
					case 1: {
						bPlayer2Wins = true;

						break;
					}
					case 2: {
						bPlayer3Wins = true;

						break;
					}
					case 3: {
						bPlayer4Wins = true;

						break;
					}

					default:
						break;
					}
				}
				if (!Balls[i]->Dead && Balls[i]->wins == 2)
				{
					switch (i)
					{
					case 0: {
						bOverallPlayer1Wins = true;

						break;
					}
					case 1: {
						bOverallPlayer2Wins = true;

						break;
					}
					case 2: {
						bOverallPlayer3Wins = true;

						break;
					}
					case 3: {
						bOverallPlayer4Wins = true;

						break;
					}

					default:
						break;
					}
				}
			}
		}
		if (DelayTemp == Delay)
		{
			Delay = 0.0f;

			for (auto Ball : Balls) {
				if (!Ball->Dead) {
					Ball->wins++;
					
					Delay = 2.0f;

					if (Ball->wins == 3) {
						nextScene = TOMAIN;
					}
				}
			}
			IsDelayed = false;
			int TempCount = 0;

			for (auto Ball : Balls) {
				if (ObjectInitialized[TempCount])
				{
					Ball->SetScale({ glm::vec3(0.1, 0.1, 0.1) });
				}
				TempCount++;
			}

			bPlayer1Wins = false;
			bPlayer2Wins = false;
			bPlayer3Wins = false;
			bPlayer4Wins = false;
			bOverallPlayer1Wins = false;
			bOverallPlayer2Wins = false;
			bOverallPlayer3Wins = false;
			bOverallPlayer4Wins = false;

			ResetBalls();

			std::ostringstream P1iConvert;
			std::ostringstream P2iConvert;
			std::ostringstream P3iConvert;
			std::ostringstream P4iConvert;

			if (ObjectInitialized[0] == true)
			{
				P1iConvert << Balls[0]->wins;
				Player1->SetText(P1iConvert.str());
			}
			if (ObjectInitialized[1] == true)
			{
				P2iConvert << Balls[1]->wins;
				Player2->SetText(P2iConvert.str());
			}
			if (ObjectInitialized[2] == true)
			{
				P3iConvert << Balls[2]->wins;
				Player3->SetText(P3iConvert.str());
			}
			if (ObjectInitialized[3] == true)
			{
				P4iConvert << Balls[3]->wins;
				Player4->SetText(P4iConvert.str());
			}
		}

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

	int TempCount = 0;

	for (auto Ball : Balls) {
		if ((ObjectInitialized[TempCount] == true))
		{
				Ball->Dead = false;
				Ball->DeadY = false;
				Ball->SpeedX = 0;
				Ball->SpeedY = 0;
		}
		TempCount++;
	}
}