#include "Scene.h"
#include "Sound.h"



Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Update()
{
}

void Scene::Init()
{
}

void Scene::Deconstruct()
{
}

void Scene::Render()
{
}

//Updated Move Function
void Scene::MoveCharacter(unsigned char KeyState[255])
{
	if (KeyState[(unsigned char)'w'] == INPUT_HOLD)
	{
		
	}
	if (KeyState[(unsigned char)'s'] == INPUT_HOLD)
	{
		
	}
	if (KeyState[(unsigned char)'a'] == INPUT_HOLD)
	{
		
	}
	if (KeyState[(unsigned char)'d'] == INPUT_HOLD) 
	{
		
	}
}

bool Scene::IsColliding(glm::vec3 C1, glm::vec3 C2, float R1, float R2)
{
	glm::vec3 temp(C2.x - C1.x, C2.y - C1.y, C2.z - C1.z);
	float distance = sqrt((temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z));
	if (distance < R1 + R2) {
		return true;
	}
	return false;
}

void Scene::ChangeNames(std::vector<std::string> _strings)
{
}

void Scene::ChangeHostNames(std::vector<std::string> _strings)
{
}

void Scene::MovePlayerOne(glm::vec3 _NewPos)
{
}

void Scene::MoveNetworkPlayer(glm::vec3 _NewPos)
{
}
