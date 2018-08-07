#pragma once
#include "dependencies\FMOD\fmod.hpp"

class Sound
{
public:
	static Sound* GetInstance();
	static void DestroyInstance();

	FMOD::Channel* Musicchannel;
	FMOD::Channel* fxchannel;
	FMOD::System* audioMgr;
	FMOD::Sound* fxSplat;
	FMOD::Sound* bgmTheme;
	FMOD::Sound* menuTheme;

	bool InitFmod();
	const bool LoadAudio();

private:
	static Sound* m_SoundManager;
	Sound();
	~Sound();
	Sound(Sound const&) = delete;
	void operator=(Sound const&) = delete;

};

