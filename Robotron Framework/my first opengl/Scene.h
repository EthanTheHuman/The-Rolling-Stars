#pragma once
#include "Camera.h"
#include "Sprite.h"
#include <vector>

enum SceneTransition {
	NOTHING,
	PREVIOUS,
	NEXT,
	TOMAIN
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
	virtual void ChangeNames(std::vector<std::string> _strings);
	virtual void ChangeHostNames(std::vector<std::string> _strings);
	virtual void MovePlayerOne(glm::vec3 _NewPos);
	virtual void MoveNetworkPlayer(glm::vec3 _NewPos);

	Camera MyCamera;
	GLuint MyProgram;
	SceneTransition nextScene = NOTHING;
	bool b_pauseMenu = false;
	int Networkmode = 0;
	bool ServerChosen = false;
	bool GameStart = false;
};

