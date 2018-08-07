#include "CubeMap.h"
#include <vector>

CubeMap::CubeMap()
{
}

CubeMap::CubeMap(Camera * _Camera, GLuint _Program, char * _Top, char * _Bottom, char * _Left, char * _Right, char * _Front, char * _Back)
{
	m_Program = _Program;
	m_Camera = _Camera;

		//------------------------------------------------------------------------------------------------------------------------------------------
		// Vertex Array Object
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Vertex Buffer Object
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData
		(
			GL_ARRAY_BUFFER,
			sizeof(VerticesCube),
			VerticesCube,
			GL_STATIC_DRAW
		);

		// Vertex Array Object Again
		glVertexAttribPointer
		(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)0
		);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer
		(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)(3 * sizeof(GLfloat))
		);

		glEnableVertexAttribArray(1);

		glVertexAttribPointer
		(
			2,
			2,
			GL_FLOAT,
			GL_FALSE,
			8 * sizeof(GLfloat),
			(GLvoid*)(6 * sizeof(GLfloat))
		);

		glEnableVertexAttribArray(2);

		// Element array buffer
		glGenBuffers(1, &ebo);	// Add "GLuint ebo" to global variables
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glBufferData
		(
			GL_ELEMENT_ARRAY_BUFFER,
			sizeof(indicesCube),
			indicesCube,
			GL_STATIC_DRAW
		);

		//------------------------------------------------------------------------------------------------------------------------------------------
		glGenTextures(1, &TempTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, TempTexture);
		int width, height;
		unsigned char* image;

		std::vector<char*> textureFilePaths;
		textureFilePaths.push_back(_Right);
		textureFilePaths.push_back(_Left);
		textureFilePaths.push_back(_Top);
		textureFilePaths.push_back(_Bottom);
		textureFilePaths.push_back(_Back);
		textureFilePaths.push_back(_Front);

		for (GLuint i = 0; i < 6; i++)
		{
			std::string fullPathName = "Textures/CubeMap/";
			fullPathName.append(textureFilePaths[i]);

			image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::Render()
{
	glUseProgram(m_Program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TempTexture);
	glUniform1i(glGetUniformLocation(m_Program, "cubeSampler"), 0);
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(1000.0f, 1000.0f, 1000.0f));
	glm::mat4 MVP = m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix() * model;
	glUniformMatrix4fv(glGetUniformLocation(m_Program, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, sizeof(indicesCube) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}


CubeMap::~CubeMap()
{
}
