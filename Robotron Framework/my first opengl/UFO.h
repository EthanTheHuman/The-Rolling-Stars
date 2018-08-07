#pragma once
#include "Entity.h"
#include <cmath>
#include <time.h>
#include "Utils2.h"

enum Type {
	SEEK,
	PURSUE,
	ARRIVAL
};
class UFO :
	public Entity
{
public:
	UFO();
	UFO(Camera * _Camera, GLuint _Shader);
	~UFO();
	void Update(glm::vec3 C1, glm::vec3 C2);
	void Render();
	void setpos(glm::vec2);
	void setType(Type);
	bool DistanceTo(glm::vec3, glm::vec3, float);
private:
	float speed = 0.02f;
	Model * UFOModel;
	float m_y = -0.1f;
	Type _Type;
	int ticks = 100;
	glm::vec3 temp;
};