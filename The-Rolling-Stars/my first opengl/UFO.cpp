#include "UFO.h"


UFO::UFO()
{
	srand((unsigned)time(NULL));
}

UFO::UFO(Camera * _Camera, GLuint _Shader)
{
	UFOModel = new Model("Models/UFO/Low_poly_UFO.obj", _Camera, _Shader);
	UFOModel->SetScale({ 0.01f, 0.01f, 0.01f });
}


UFO::~UFO()
{
	delete UFOModel;
}


void UFO::Update(glm::vec3 C1, glm::vec3 C2)
{
	if (_Type == SEEK)
	{
		if (DistanceTo(C1, glm::vec3(m_x, m_y, m_z), 5)) {
			temp = C1;
		}
		else if (ticks == 0) {
			temp.x = m_x - 5 + rand() % 10;
			temp.y = 0.0f;
			temp.z = m_z - 5 + rand() % 10;
			ticks = 100;
		}
		else {
			ticks--;
		}
	}
	else if (_Type == PURSUE)
	{
		if (DistanceTo(C1, glm::vec3(m_x, m_y, m_z), 5)) {
			temp = C1;
		}
		else if (ticks == 0) {
			temp.x = m_x - 5 + rand() % 10;
			temp.y = 0.0f;
			temp.z = m_z - 5 + rand() % 10;
			ticks = 100;
		}
		else {
			ticks--;
		}
		temp.x = temp.x + (C2.x * 5);
		temp.y = temp.y + (C2.y * 5);
	}

	if (_Type == ARRIVAL)
	{
		if (DistanceTo(C1, glm::vec3(m_x, m_y, m_z), 5)) {
			temp = C1;
		}
		else if (ticks == 0) {
			temp.x = m_x - 5 + rand() % 10;
			temp.y = 0.0f;
			temp.z = m_z - 5 + rand() % 10;
			ticks = 100;
		}
		else {
			ticks--;
		}
		float distance = sqrt(pow(temp.x - m_x, 2) + pow(temp.z - m_z, 2));
		float directionX = (temp.x - m_x) / distance;
		float directionY = (temp.z - m_z) / distance;

		m_x += directionX * (distance * speed)/2;
		m_z += directionY * (distance * speed)/2;
	}
	else
	{
		float distance = sqrt(pow(temp.x - m_x, 2) + pow(temp.z - m_z, 2));
		float directionX = (temp.x - m_x) / distance;
		float directionY = (temp.z - m_z) / distance;

		m_x += directionX * speed;
		m_z += directionY * speed;
	}
}

void UFO::Render()
{
	UFOModel->SetTranslation({ m_x, m_y, m_z });
	UFOModel->Render();
}

void UFO::setpos(glm::vec2 pos)
{
	m_x = pos.x;
	m_z = pos.y;
}

void UFO::setType(Type type)
{
	_Type = type;
}

bool UFO::DistanceTo(glm::vec3 C1, glm::vec3 C2, float R1)
{
	glm::vec3 temp(C2.x - C1.x, C2.y - C1.y, C2.z - C1.z);
	float distance = sqrt((temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z));
	if (distance < R1) {
		return true;
	}
	return false;
}