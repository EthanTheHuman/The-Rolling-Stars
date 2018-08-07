#include "UISprite.h"

UISprite::UISprite()
{

}

UISprite::UISprite(char * _filename, Camera * _camera, GLuint _program)
{
	//------------------------------------------------------------------------------------------------------------------------------------------
	glUniform3f(glGetUniformLocation(_program, "textColor"), 255, 255, 255);
	glm::mat4 proj = glm::ortho(0.0f, (GLfloat)SRCWIDTH, 0.0f, (GLfloat)SRCHEIGHT);
	glUniformMatrix4fv(glGetUniformLocation(_program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

	//Get this out of the way
	m_Camera = _camera;
	m_Program = _program;
	glUseProgram(m_Program);

	//------------------------------------------------------------------------------------------------------------------------------------------

	// Initialise square with rainbow colors
	GLfloat SquareVertices2[] =
	{
		// Positions		// Colors			// Texture mapping
		-1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,	0, 0, // Top Left
		1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 1.0f,	1, 0, // Top Right
		1.0f, -1.0f, 0.0f,	0.0f, 1.0f, 0.0f,	1, 1, // Bottom Right
		-1.0f, -1.0f, 0.0f,	0.0f, 0.0f, 1.0f,	0, 1 // Bottom Left
	};

	// Square indices
	GLuint SquareIndices[] =
	{
		0, 1, 2, // First Triangle
		0, 2, 3 // Second Triangle
	};

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
		sizeof(SquareVertices2),
		SquareVertices2,
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
		sizeof(SquareIndices),
		SquareIndices,
		GL_STATIC_DRAW
	);

	//------------------------------------------------------------------------------------------------------------------------------------------
	glGenTextures(1, &TempTexture);
	glBindTexture(GL_TEXTURE_2D, TempTexture);

	// Loading texture
	unsigned char* image = SOIL_load_image
	(
		_filename,			// File path/name
		&width,				// Output for image width
		&height,			// Output for number of channels
		0,					// Number of channels
		SOIL_LOAD_RGBA		// Load RGB values only
	);

	glTexImage2D
	(
		GL_TEXTURE_2D,		// Type of texture
		0,					// Mipmap level, 0 for base
		GL_RGBA,				// Number of color components in texture
		width,				// Width of texture
		height,				// Height of texture
		0,					// Must be 0
		GL_RGBA,				// Format for the pixel data
		GL_UNSIGNED_BYTE,	// Data type of the pixel data
		image				// Pointer to image data in memory
	);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);



	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLfloat bordercolor[] = { 1.0f, 0.0f,0.0f,0.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bordercolor);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_Texture = TempTexture;

	RefreshMVP();

	SetScale({ 1,1,0 });
	//------------------------------------------------------------------------------------------------------------------------------------------
}


UISprite::~UISprite()
{
}

void UISprite::render()
{
	glUseProgram(m_Program);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	RefreshMVP();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(m_Program, "SpriteTex"), 0);
	glBindVertexArray(vao);			// Bind VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);			// Unbind VAO
}

void UISprite::RefreshMVP()
{
	m_MVPMatrix = glm::mat4();
	//Projection * view * model
	m_MVPMatrix = ((m_ModelMatrix));
	//m_MVPMatrix = glm::mat4();
	GLint MVPLoc = glGetUniformLocation(m_Program, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(m_MVPMatrix));

}

void UISprite::AddTranslation(glm::vec3 _Translation)
{
	m_TranslationMatrix = glm::translate(m_TranslationMatrix, _Translation);
	RefreshModelMatrix();
	RefreshMVP();
}

void UISprite::SetRotation(glm::vec3 _Rotation)
{
	m_RotationMatrix = glm::rotate(glm::mat4(), glm::radians(_Rotation.x), glm::vec3(1, 0, 0));
	m_RotationMatrix = glm::rotate(glm::mat4(), glm::radians(_Rotation.y), glm::vec3(0, 1, 0));
	m_RotationMatrix = glm::rotate(glm::mat4(), glm::radians(_Rotation.z), glm::vec3(0, 0, 1));
	RefreshModelMatrix();
	RefreshMVP();
}

void UISprite::AddRotation(glm::vec3 _Rotation)
{
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(_Rotation.x), glm::vec3(1, 0, 0));
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(_Rotation.y), glm::vec3(0, 1, 0));
	m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(_Rotation.z), glm::vec3(0, 0, 1));
	RefreshModelMatrix();
	RefreshMVP();
}

void UISprite::SetScale(glm::vec3 _Scale)
{
	// Scaling while retaining aspect ratio
	glm::vec3 NewScale = { (_Scale.x * (width)) / width, (_Scale.y * (height)) / width, _Scale.z };
	m_ScaleMatrix = glm::scale(glm::mat4(), NewScale);
	RefreshModelMatrix();
	RefreshMVP();
}

void UISprite::AddScale(glm::vec3 _Scale)
{
	m_ScaleMatrix = glm::scale(m_ScaleMatrix, _Scale);
	RefreshModelMatrix();
	RefreshMVP();
}

void UISprite::SetTranslation(glm::vec3 _Translation)
{
	m_TranslationMatrix = glm::translate(glm::mat4(), _Translation);
	RefreshModelMatrix();
	RefreshMVP();
}

void UISprite::RefreshModelMatrix()
{
	m_ModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
}
