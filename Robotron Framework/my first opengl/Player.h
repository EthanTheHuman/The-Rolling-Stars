#pragma once
#include "Entity.h"

class Player :
	public Entity
{
public:
	Player();
	Player(Camera * _Camera, GLuint _Shader);
	~Player();
	void vertical(bool _direction);
	void horizontal(bool _direction);
	void Update();
	void Render();
	void SetRotation(glm::vec3 _rotation);
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 _NewPosition);

private:
	float speed = 0.05f;
	Model * PlayerModel;
	int i_Rotation;
	glm::vec3 m_Direction = {0, 0, 0};
	float TempX = 0.0f;
	float TempZ = 0.0f;
};

