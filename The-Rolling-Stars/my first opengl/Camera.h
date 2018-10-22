#pragma once
#include <iostream>
#include "ShaderLoader.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include <iterator>
#include <map>

enum InputState {
	INPUT_FIRST_RELEASE, // First frame of Up state
	INPUT_RELEASED, // Default State (Up)
	INPUT_FIRST_PRESS, // First frame of Down state
	INPUT_HOLD, // Key is held Down
};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal);
	~Camera();

	void Update();
	
	glm::mat4 GetViewMatrix();
	void SetViewMatrix();
	void SetViewMatrix(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal);

	glm::mat4 GetProjectionMatrix();
	void SetProjectionMatrix();

	glm::vec3 GetCameraPosition();
	void SetCameraPosition(glm::vec3 _Position);

	glm::vec3 GetCameraFacing();
	void SetCameraFacing(glm::vec3 _Facing);

	glm::vec3 GetCameraNormal();
	void SetCameraNormal(glm::vec3 _Normal);

	void LookAt();
	void LookAt(glm::vec3 _Position, glm::vec3 _Facing, glm::vec3 _Normal);

private:
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFacing = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	float SourceWidth = 640;
	float SourceHeight = 480;
};

