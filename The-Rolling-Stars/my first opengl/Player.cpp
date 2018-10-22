#include "Player.h"



Player::Player()
{
}

Player::Player(Camera * _Camera, GLuint _Shader)
{
	PlayerModel = new Model("Models/h2f2obj/f.obj", _Camera, _Shader);
	PlayerModel->SetScale({ 0.2f, 0.2f, 0.2f });
}

Player::~Player()
{
	delete PlayerModel;
}

void Player::vertical(bool _direction)
{
	if (_direction)
	{
		m_z += speed;
	}
	else if (!_direction)
	{
		m_z -= speed;
	}
}

void Player::horizontal(bool _direction)
{
	if (!_direction)
	{
		m_x += speed;
	}
	else if (_direction)
	{
		m_x -= speed;
	}
}

void Player::Update()
{
	m_Direction = {m_x - TempX, 0, m_z - TempZ };
	TempX = m_x;
	TempZ = m_z;
}

void Player::Render()
{
	PlayerModel->SetTranslation({ m_x, m_y, m_z });
	PlayerModel->Render();
}

void Player::SetRotation(glm::vec3 _rotation)
{
	PlayerModel->SetRotation(_rotation);
}

glm::vec3 Player::GetPosition()
{
	return m_Direction;
}

void Player::SetPosition(glm::vec3 _NewPosition)
{
	PlayerModel->SetTranslation(_NewPosition);
}
