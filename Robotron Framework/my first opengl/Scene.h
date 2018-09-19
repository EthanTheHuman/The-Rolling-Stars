#pragma once
#include "Camera.h"
#include "Sprite.h"
#include "CXBOXController.h"
#include <vector>

enum SceneTransition {
	NOTHING,
	PREVIOUS,
	NEXT,
	TOMAIN,
	EXIT
};

class Scene
{
public:
	Scene();
	~Scene();
	virtual void Update();
	virtual void Init();
	virtual void Deconstruct();
	virtual void Render();
	virtual void MoveCharacter(unsigned char KeyState[255]);
	virtual bool IsColliding(glm::vec3, glm::vec3, float, float);
	virtual void SetControlers(std::vector<CXBOXController*> Controllers);

	Camera MyCamera;
	GLuint MyProgram;
	SceneTransition nextScene = NOTHING;
	bool b_pauseMenu = false;
};

