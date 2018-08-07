#pragma once
#include <iostream>
#include "ShaderLoader.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Utils2.h"
#include "Camera.h"

// Sprite class made for storing and rendering sprites
// Contains a filename to a source image, and integers to indicate the size of said sprite
class UISprite
{
public:
	UISprite();
	UISprite(char * _filename, Camera * _camera, GLuint _program);
	~UISprite();

	//Simple
	void render();

	//Refresh Matrices
	void RefreshMVP();
	void RefreshModelMatrix();

	//Translation
	void SetTranslation(glm::vec3 _Translation);
	void AddTranslation(glm::vec3 _Translation);

	//Rotation
	void SetRotation(glm::vec3 _Rotation);
	void AddRotation(glm::vec3 _Rotation);

	//Scale
	void SetScale(glm::vec3 _Scale);
	void AddScale(glm::vec3 _Scale);

private:
	//Texture
	GLuint m_Texture;
	int width = 200;
	int height = 200;

	//Matrices
	glm::mat4 m_TranslationMatrix = glm::mat4();
	glm::mat4 m_RotationMatrix = glm::mat4();
	glm::mat4 m_ScaleMatrix = glm::mat4();
	glm::mat4 m_ModelMatrix = glm::mat4();
	glm::mat4 m_MVPMatrix = glm::mat4();

	//Camera
	Camera * m_Camera;

	//Other Stuff
	GLuint vbo;
	GLuint vao;
	GLuint ebo;
	GLuint m_Program;
	GLuint TempTexture;
	ShaderLoader shaderloader;
};
