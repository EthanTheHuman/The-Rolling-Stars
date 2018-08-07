#include "Sound.h"

Sound* Sound::m_SoundManager;

Sound * Sound::GetInstance()
{
	if (!m_SoundManager)
	{
		m_SoundManager = new Sound();
	}
	return m_SoundManager;
}

void Sound::DestroyInstance()
{
	if (m_SoundManager)
	{
		delete m_SoundManager;
	}
	m_SoundManager = nullptr;
}

bool Sound::InitFmod()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&audioMgr);
	if (result != FMOD_OK)
	{
		return false;
	}

	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		return false;
	}
	return true;
}

const bool Sound::LoadAudio()
{
	FMOD_RESULT result;
	result = audioMgr->createSound("Sounds/Splat.wav", FMOD_DEFAULT, 0, &fxSplat);
	result = audioMgr->createSound("Sounds/Game.mp3", FMOD_DEFAULT, 0, &bgmTheme);
	result = audioMgr->createSound("Sounds/Menu.mp3", FMOD_DEFAULT, 0, &menuTheme);

	bgmTheme->setMode(FMOD_LOOP_NORMAL);
	menuTheme->setMode(FMOD_LOOP_NORMAL);

	return true;
}

Sound::Sound()
{
	InitFmod();
	LoadAudio();
}


Sound::~Sound()
{
}