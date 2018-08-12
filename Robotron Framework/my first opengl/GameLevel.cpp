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
	Player1->Init("Resources/Textures/Balls/Player1/Ball.png", MyCamera, SpriteShader);
	Player2->Init("Resources/Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader);
	Player3 = BallPlayer("Resources/Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader);
	Player4 = BallPlayer("Resources/Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader);
}

void GameLevel::Deconstruct()
{

}

void GameLevel::Render()
{

}

void GameLevel::Update()
{

}

void GameLevel::MoveCharacter(unsigned char KeyState[255])
{

}