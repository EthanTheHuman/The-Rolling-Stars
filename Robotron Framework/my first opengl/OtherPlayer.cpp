#include "OtherPlayer.h"



OtherPlayer::OtherPlayer()
{
}

OtherPlayer::OtherPlayer(Camera * _Camera, GLuint _Shader)
{
	PlayerModel = new Model("Models/h2f2obj/f.obj", _Camera, _Shader);
	PlayerModel->SetScale({ 0.2f, 0.2f, 0.2f });
}

OtherPlayer::~OtherPlayer()
{
	delete PlayerModel;
}

void OtherPlayer::vertical(bool _direction)
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

void OtherPlayer::horizontal(bool _direction)
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

void OtherPlayer::Update()
{
	m_Direction = { m_x - TempX, 0, m_z - TempZ };
	TempX = m_x;
	TempZ = m_z;
}

void OtherPlayer::Render()
{
	PlayerModel->SetTranslation({ m_x, m_y, m_z });
	PlayerModel->Render();
}

void OtherPlayer::SetRotation(glm::vec3 _rotation)
{
	PlayerModel->SetRotation(_rotation);
}

glm::vec3 OtherPlayer::GetPosition()
{
	return m_Direction;
}

void OtherPlayer::SetPosition(glm::vec3 _NewPosition)
{
	PlayerModel->SetTranslation(_NewPosition);
}
