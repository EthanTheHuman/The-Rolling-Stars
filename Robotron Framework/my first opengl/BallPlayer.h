#pragma once
#include "Sprite.h"
#include "CXBOXController.h"
class BallPlayer : Sprite
{
public:
	BallPlayer();
	~BallPlayer();
	void Init(char * _filename, Camera * _camera, GLuint _program, CXBOXController* Controller);
	void render();
	void MoveCharacter(unsigned char KeyState[255]);
	void UpdateCharater();
	void ChangePosition(glm::vec2 pos);
	float ColisionRadius = 0.1;
	float Xpos;
	float Ypos;
	float SpeedX;
	float SpeedY;
	float mass = ColisionRadius * 10.f;
	bool Dead = false;
	bool DeadY = false;
private:
	float friction = 0.0005;
	float acceleration = 0.001;
	CXBOXController* m_pCXboxController;
};