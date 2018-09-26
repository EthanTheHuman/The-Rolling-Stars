#pragma once
#include "Scene.h"

// Dependencies
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

#include "Camera.h"
#include "GameManager.h"
#include "Sound.h"
#include "Sprite.h"
#include "UISprite.h"
#include "Model.h"
#include "TextLabel.h"
#include "CubeMap.h"
#include "Player.h"
#include "UFO.h"
#include "dependencies\FMOD\fmod.hpp"

enum Menus {
	MAIN,
	PLAY,
	CONTROL,
	COOP,
	HOST,
	JOIN,
	LOBBY
};

class MainMenu :
	public Scene
{
public:
	MainMenu();
	void Init();
	void Deconstruct();
	~MainMenu();
	void Render();
	void Update();
	void MoveCharacter(unsigned char KeyState[255]);
	void SetControlers(std::vector<CXBOXController*> Controllers);

private:
	// List of objects
	Camera * MyCamera;
	std::vector<TextLabel*> mainMenu;
	std::vector<TextLabel*> settings;
	std::vector<TextLabel*> credits;

	std::vector<CXBOXController*> XBoxControllers;

	CubeMap * MySkybox;
	ShaderLoader shaderloader;
	UISprite * Title;

	// List of Shaders
	GLuint UISpriteShader;
	GLuint SkyboxShader;
	GLuint TextLableShader;

	//menu stuff
	int selection = 0;
	Menus menu = MAIN;

	bool IsMainMenu = true;
	bool IsSettings = false;
	bool IsCredits = false;

	//Player ready up messages
	TextLabel* Player1;
	TextLabel* Player2;
	TextLabel* Player3;
	TextLabel* Player4;
};
