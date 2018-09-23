#include "GameManager.h"
#include "MainMenu.h"
#include "GameLevel.h"

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
	if (pScenes[CurrentScene]->nextScene == EXIT) {
		PostQuitMessage(0); 
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
	std::vector<CXBOXController*> Controllers;
	CXBOXController* m_pCXboxController1 = new CXBOXController(1);
	CXBOXController* m_pCXboxController2 = new CXBOXController(2);
	CXBOXController* m_pCXboxController3 = new CXBOXController(3);
	CXBOXController* m_pCXboxController4 = new CXBOXController(4);
	Controllers.push_back(m_pCXboxController1);
	Controllers.push_back(m_pCXboxController2);
	Controllers.push_back(m_pCXboxController3);
	Controllers.push_back(m_pCXboxController4);

	MainMenu* newMainMenu = new MainMenu();
	newMainMenu->SetControlers(Controllers);
	pScenes.push_back(newMainMenu);

	GameLevel* newGameLevel = new GameLevel();
	newGameLevel->SetControlers(Controllers);
	pScenes.push_back(newGameLevel);
}


GameManager::~GameManager()
{
}