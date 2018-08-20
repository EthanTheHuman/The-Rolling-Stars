#pragma once
#include "Sprite.h"
class BallPlayer : Sprite
{
public:
	BallPlayer();
	~BallPlayer();
	void Init(char * _filename, Camera * _camera, GLuint _program);
	void render();
	void MoveCharacter(unsigned char KeyState[255]);
	void UpdateCharater();
	bool BorderCheck();
	glm::vec2 ReturnPosition();
	void ChangePosition(glm::vec2 pos);
	float ColisionRadius = 0.1;
	float Xpos;
	float Ypos;
private:
	float SpeedX;
	float SpeedY;
	float friction = 0.0005;
	float parafriction = 1.8;
	float acceleration = 0.005;
};

