#pragma once
#include <vector>
#include "Scene.h"

class GameManager
{
public:
	static GameManager* GetInstance();
	static void DestroyInstance();

	// switch scene (takes in int)
	void SwitchScene(int _Placement);
	// Render current scene
	void render();
	void update();
	// Update current scene

	// Vector of scenes
	std::vector<Scene*> pScenes;
	// Current scene int
	int CurrentScene = 0;

	//Inputs
	Scene* CurrentSceneClass();

private:
	static GameManager* m_Manager;
	GameManager();
	~GameManager();
	GameManager(GameManager const&) = delete;
	void operator=(GameManager const&) = delete;
	
};