#pragma once
#include <iostream>
#include "ShaderLoader.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"


#define SRCWIDTH 800
#define SRCHEIGHT 600

struct PositionStruct
{
	float x;
	float y;
	float z;
};

struct ColorStruct
{
	float r;
	float g;
	float b;
};

struct TexCoordStruct
{
	float x;
	float y;
};

class Utils2
{
public:
	Utils2();
	~Utils2();
	PositionStruct CreatePositionStruct();
	void CreateTexCoordStruct();
	void CreateVertexFormatStruct();
	void CreateIndexFormatStruct();
	void SetQuadVertices();
	void SetResolution();
};