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
	void SetScale(glm::vec3 scale);
	void AddScale(glm::vec3 scale);
	glm::vec3 GetScale();
	float ColisionRadius = 0.1;
	float Xpos;
	float Ypos;
	float SpeedX;
	float SpeedY;
	float mass = ColisionRadius * 10.f;
	bool Dead = false;
	bool DeadY = false;
	int wins = 0;
private:
	float friction = 0.0003;
	float acceleration = 0.0012;
	CXBOXController* m_pCXboxController = nullptr;
};