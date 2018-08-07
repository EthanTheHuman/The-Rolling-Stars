#include "Entity.h"



Entity::Entity()
{
}

Entity::Entity(int _x, int _y)
{
	m_x = _x;
	m_y = _y;
}


Entity::~Entity()
{
}

glm::vec3 Entity::GetPos()
{
	return glm::vec3(m_x, m_y, m_z);
}
