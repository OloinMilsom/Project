#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

//FMOD includes
#pragma comment(lib,"fmodex_vc.lib")
#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>

class SoundManager{
private:
	static SoundManager * m_instance;
	SoundManager();

	std::vector<FMOD::Sound *> m_effects;
	std::vector<FMOD::Sound *> m_music;
	FMOD::System * m_system;
	FMOD::Channel * m_effectsChannel;
	FMOD::Channel * m_musicChannel;
	bool m_effectsMute;
	bool m_musicMute;
	//FMOD::ChannelGroup *channelMusic;
public:
	~SoundManager();
	static SoundManager * getInstance();
	void playEffect(int i);
	void playMusic(int i);
	void muteEffects();
	void muteMusic();
};

#endif