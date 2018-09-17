#include "BallPlayer.h"
#include "CXBOXController.h"

CXBOXController* m_pCXboxController = new CXBOXController(1);

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
	if (m_pCXboxController->GetState().Gamepad.sThumbLX == -32768)
	{
		SpeedX += acceleration;

	}
	if (m_pCXboxController->GetState().Gamepad.sThumbLX == 32767)
	{
		SpeedX -= acceleration;
	}
	if (m_pCXboxController->GetState().Gamepad.sThumbLY == 32767)
	{
		SpeedY += acceleration;
	}
	if (m_pCXboxController->GetState().Gamepad.sThumbLY == -32768)
	{
		SpeedY -= acceleration;
	}

	//Diagonal

	if (m_pCXboxController->GetState().Gamepad.sThumbLX == -32768 && m_pCXboxController->GetState().Gamepad.sThumbLY == 32767)
	{
		SpeedX += acceleration;
		SpeedY += acceleration;
	}
	if (m_pCXboxController->GetState().Gamepad.sThumbLX == 32767 && m_pCXboxController->GetState().Gamepad.sThumbLY == 32767)
	{
		SpeedX -= acceleration;
		SpeedY += acceleration;
	}
	if (m_pCXboxController->GetState().Gamepad.sThumbLX == 32767 && m_pCXboxController->GetState().Gamepad.sThumbLY == -32767)
	{
		SpeedY += acceleration;
		SpeedY -= acceleration;
	}
	if (m_pCXboxController->GetState().Gamepad.sThumbLX == -32768 && m_pCXboxController->GetState().Gamepad.sThumbLY == -32767)
	{
		SpeedX -= acceleration;
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

	//Boundaries
	if (Xpos + SpeedX < -2.25f)
	{
		Sprite::SetTranslation({ Xpos, Ypos, 0 });
		SpeedX = 0;
		SpeedY = 0;
		return;
	}
	if (Xpos + SpeedX > 2.25f)
	{
		Sprite::SetTranslation({ Xpos, Ypos, 0 });
		SpeedX = 0;
		SpeedY = 0;
		return;
	}
	if (Ypos + SpeedY < -1.75f)
	{
		Sprite::SetTranslation({ Xpos, Ypos, 0 });
		SpeedX = 0;
		SpeedY = 0;
		return;
	}
	if (Ypos + SpeedY > 1.75f)
	{
		Sprite::SetTranslation({ Xpos, Ypos, 0 });
		SpeedX = 0;
		SpeedY = 0;
		return;
	}


	//Update player posistion
	Ypos += SpeedY;
	Xpos += SpeedX;
	Sprite::SetTranslation({ Xpos, Ypos, 0 });
}

void BallPlayer::ChangePosition(glm::vec2 pos) {
	Xpos = pos.x;
	Ypos = pos.y;
}
