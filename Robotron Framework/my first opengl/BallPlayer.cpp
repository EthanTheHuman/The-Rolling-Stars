#include "BallPlayer.h"



BallPlayer::BallPlayer()
{
}

BallPlayer::~BallPlayer()
{

}
void BallPlayer::Init(char * _filename, Camera * _camera, GLuint _program) {
	Sprite::Init( _filename, _camera, _program);
	Sprite::SetScale({ 0.1, 0.1, 0 });
}

void BallPlayer::render()
{
	Sprite::render();
}

void BallPlayer::MoveCharacter(unsigned char KeyState[255])
{
	if (KeyState[(unsigned char)'a'] == INPUT_HOLD)
	{
		SpeedX += acceleration;
	}
	if (KeyState[(unsigned char)'d'] == INPUT_HOLD)
	{
		SpeedX -= acceleration;
	}
	if (KeyState[(unsigned char)'w'] == INPUT_HOLD)
	{
		SpeedY += acceleration;
	}
	if (KeyState[(unsigned char)'s'] == INPUT_HOLD)
	{
		SpeedY -= acceleration;
	}
}

void BallPlayer::UpdateCharater()
{
	if (SpeedX < friction && SpeedX > -friction) {
		SpeedX = 0;
	}
	else {
		if (SpeedX > 0) {
			SpeedX -= friction;
			//SpeedX = SpeedX / parafriction;
		}
		if (SpeedX < 0) {
			SpeedX += friction;
		}
	}
	if (SpeedY < friction && SpeedY > -friction) {
		SpeedY = 0;
	}
	else {
		if (SpeedY > 0) {
			SpeedY -= friction;
		}
		if (SpeedY < 0) {
			SpeedY += friction;
		}
	}
	Ypos += SpeedY;
	Xpos += SpeedX;
	Sprite::SetTranslation({ Xpos, Ypos, 0 });
}

glm::vec2 BallPlayer::ReturnPosition()
{
	return { Xpos, Ypos, };
}

void BallPlayer::ChangePosition(glm::vec2 pos) {
	Xpos = pos.x;
	Ypos = pos.y;
}
