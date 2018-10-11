#pragma once
#include "Scene.h"
#include "BallPlayer.h";

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
#include "CubeMap.h"
#include "Player.h"
#include "EllipseCollisionTest.h"
#include "TextLabel.h"


class GameLevel :
	public Scene
{
public:
	GameLevel();
	~GameLevel();

	void Init();
	void Deconstruct();

	void Render();
	void Update();
	void MoveCharacter(unsigned char KeyState[255]);
	void SetControlers(std::vector<CXBOXController*> Controllers);

	bool CheckCollision(BallPlayer * one, BallPlayer * two);
	void ResetBalls();

private:

	std::vector<CXBOXController*> XBoxControllers;

	//Graphics stuff
	Camera* MyCamera;
	CubeMap * MySkybox;
	ShaderLoader shaderloader;

	//Shaders
	GLuint SpriteShader;
	GLuint UISpriteShader;
	GLuint ModelBasicShader;
	GLuint AmbientShader;
	GLuint TextLableShader;
	GLuint SkyboxShader;

	//Game Objects
	std::vector <BallPlayer*> Balls;
	std::vector <pair<BallPlayer*, BallPlayer*>> CollidingPairs;
	Sprite* Arena;
	Sprite* ScoreBar;

	//HUD
	TextLabel* Player1;
	TextLabel* Player2;
	TextLabel* Player3;
	TextLabel* Player4;

	//Arena Collision
	double ArenaX = 0.0;
	double ArenaY = -0.5;
	double ArenaW = 1;
	double ArenaH = 2;
};