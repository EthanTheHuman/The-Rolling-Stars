#pragma once
// Dependencies
#include <iostream>
#include "ShaderLoader.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Sprite.h"
#include "Model.h"

class Entity
{
public:
	Entity();
	Entity(int _x, int _y);
	~Entity();
	glm::vec3 GetPos();

public:
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
	Sprite m_Sprite;
	int ID;
};

