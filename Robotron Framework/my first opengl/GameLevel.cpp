#include "GameLevel.h"




GameLevel::GameLevel()
{
	BallPlayer Player1 = BallPlayer("Resources/Textures/Balls/Player1/Ball.png", MyCamera, SpriteShader);
	BallPlayer Player2 = BallPlayer("Resources/Textures/Balls/Player2/Ball.png", MyCamera, SpriteShader);
	BallPlayer Player3 = BallPlayer("Resources/Textures/Balls/Player3/Ball.png", MyCamera, SpriteShader);
	BallPlayer Player4 = BallPlayer("Resources/Textures/Balls/Player4/Ball.png", MyCamera, SpriteShader);
}


GameLevel::~GameLevel()
{

}

void
GameLevel::Init()
{

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