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
	std::vector<FMOD::Sound *> m_spatial;
	FMOD::System * m_system;
	FMOD::Channel * m_effectsChannel;
	FMOD::Channel * m_musicChannel;
	FMOD::Channel * m_spatialChannel;
	FMOD::Reverb * m_reverb;
	FMOD_REVERB_PROPERTIES m_prop;
	bool m_effectsMute;
	bool m_musicMute;
	bool m_spatialMute;
	bool m_reverbMute;
	//FMOD::ChannelGroup *channelMusic;
public:
	~SoundManager();
	static SoundManager * getInstance();
	void playEffect(int i);
	void playMusic(int i);
	void playSpatial(int i);
	void stopSpatial();
	void initSpatial(sf::Vector2f sourcePos);
	void updateSpatial(sf::Vector2f listenerPos, sf::Vector2f listenerVel);
	void updateReverb(FMOD_REVERB_PROPERTIES p);
	void muteEffects();
	void muteMusic();
	void muteSpatial();
	void muteReverb();
};

#endif