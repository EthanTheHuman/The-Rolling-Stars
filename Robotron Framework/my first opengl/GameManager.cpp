#include "GameManager.h"
#include "MainMenu.h"

GameManager* GameManager::m_Manager;

GameManager * GameManager::GetInstance()
{
	if (!m_Manager)
	{
		m_Manager = new GameManager();
	}
	return m_Manager;
}

void GameManager::DestroyInstance()
{
	if (m_Manager)
	{
		delete m_Manager;
	}
	m_Manager = nullptr;
}

void GameManager::SwitchScene(int _Placement)
{
	CurrentScene = _Placement;
	pScenes[CurrentScene]->Init();
}

void GameManager::render()
{
	pScenes[CurrentScene]->Render();
}

void GameManager::update()
{
	if (pScenes[CurrentScene]->b_pauseMenu == false) {
		pScenes[CurrentScene]->Update();
	}
	if (pScenes[CurrentScene]->nextScene == NEXT) {
		pScenes[CurrentScene]->Deconstruct();
		CurrentScene++;
		pScenes[CurrentScene]->Init();
	}
	if (pScenes[CurrentScene]->nextScene == PREVIOUS) {
		pScenes[CurrentScene]->Deconstruct();
		CurrentScene--;
		pScenes[CurrentScene]->Init();
	}
	if (pScenes[CurrentScene]->nextScene == TOMAIN) {
		pScenes[CurrentScene]->Deconstruct();
		CurrentScene = 0;
		pScenes[CurrentScene]->Init();
	}
	if (pScenes[CurrentScene]->nextScene == NOTHING) {
		//do NUTHING
	}
}

Scene* GameManager::CurrentSceneClass()
{
	return pScenes[CurrentScene];
}

GameManager::GameManager()
{
	MainMenu* newMainMenu = new MainMenu();
	pScenes.push_back(newMainMenu);
}


GameManager::~GameManager()
{
}
