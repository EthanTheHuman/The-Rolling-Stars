#pragma once

#include "Camera.h"

class CubeMap
{
public:
	CubeMap();
	CubeMap(Camera * _Camera, GLuint _Program, char * _Top, char * _Bottom, char * _Left, char * _Right, char * _Front, char * _Back);
	void Render();
	~CubeMap();

private:
	GLuint TempTexture;
	GLuint m_Program;
	Camera * m_Camera;
	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	GLfloat VerticesCube[192] =
	{
		// Positions			// Colors			// Texture mapping
		// Front Face
		-1.0f,  1.0f, 1.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,	// Top Left
		1.0f,  1.0f, 1.0f,		1.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// Top Right
		1.0f, -1.0f, 1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,	// Bottom Right
		-1.0f, -1.0f, 1.0f,		1.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// Bottom Left

		// Right Face
		1.0f,  1.0f,  1.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// Top Left
		1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// Top Right
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// Bottom Right
		1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 1.0f,	0.0f, 1.0f,	// Bottom Left

		// Back Face
		1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// Top Left
		-1.0f,  1.0f, -1.0f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,	// Top Right
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// Bottom Right
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// Bottom Left

		// Left Face
		-1.0f,  1.0f, -1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Top Left
		-1.0f,  1.0f,  1.0f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,	// Top Right
		-1.0f, -1.0f,  1.0f,	1.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// Bottom Right
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// Bottom Left

		// Top Face
		-1.0f,  1.0f, -1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Top Left
		1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// Top Right
		1.0f,  1.0f,  1.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// Bottom Right
		-1.0f,  1.0f,  1.0f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,	// Bottom Left

		// Bottom Face
		-1.0f, -1.0f,  1.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Top Left
		1.0f, -1.0f,  1.0f,		0.0f, 1.0f, 1.0f,	1.0f, 0.0f,	// Top Right
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// Bottom Right
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f	// Bottom Left
	};
	// Square indices
	GLuint indicesCube[36] =
	{
		// Front Face
		0, 1, 2, // First Triangle
		0, 2, 3, // Second Triangle

		// Right Face
		4, 5, 6,
		4, 6, 7,

		// Back Face
		8, 9, 10,
		8, 10, 11,

		// Left Face
		12, 13, 14,
		12, 14, 15,

		// Top Face
		16, 17, 18,
		16, 18, 19,

		// Bottom Face
		20, 21, 22,
		20, 22, 23
	};
};

