#include "stdafx.h"
#include "SoundManager.h"

SoundManager * SoundManager::m_instance = nullptr;

SoundManager::SoundManager(){
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_system);         // Create the main system object.
	if (result != FMOD_OK)	{
		exit(-1);
	}
	result = m_system->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
	if (result != FMOD_OK){;
		exit(-1);
	}

	// effects
	FMOD::Sound * audio;
	result = m_system->createSound("res/sounds/button.wav", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){
		exit(-1);
	}
	m_effects.push_back(audio);

	// music
	result = m_system->createSound("res/sounds/gameMusic.mp3", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){
		exit(-1);
	}
	m_music.push_back(audio);

	// spatial
	result = m_system->createSound("res/sounds/gong.wav", FMOD_LOOP_NORMAL | FMOD_3D, 0, &audio);
	if (result != FMOD_OK){
		exit(-1);
	}
	m_spatial.push_back(audio);
	//need this for sound fall off
	//m_musicChannel->setChannelGroup(channelMusic);
	//m_effectsChannel->setChannelGroup(channelEffects);
}

SoundManager::~SoundManager(){

}

SoundManager * SoundManager::getInstance(){
	if (m_instance == nullptr){
		m_instance = new SoundManager();
	}
	return m_instance;
}

void SoundManager::playEffect(int i){
	if (!m_effectsMute){
		if (i >= 0 && i < m_effects.size())
			m_system->playSound(FMOD_CHANNEL_FREE, m_effects[i], false, &m_effectsChannel);
	}
}

void SoundManager::playMusic(int i){
	if (i >= 0 && i < m_music.size()){
		//m_musicChannel->setPaused(false);
		m_system->playSound(FMOD_CHANNEL_FREE, m_music[i], false, &m_musicChannel);
		m_musicChannel->setMode(FMOD_LOOP_NORMAL);
		m_musicChannel->setLoopCount(-1);
		m_musicChannel->setVolume(0.1f);
	}
}

void SoundManager::playSpatial(int i){
	if (i >= 0 && i < m_spatial.size()){
		
		//m_musicChannel->setPaused(false);
		m_system->playSound(FMOD_CHANNEL_FREE, m_spatial[i], false, &m_spatialChannel);
		m_spatialChannel->setMode(FMOD_LOOP_NORMAL | FMOD_3D);
		m_spatialChannel->setLoopCount(-1);
	}
}

void SoundManager::updateSpatial(sf::Vector2f listenerPos, sf::Vector2f listenerVel, sf::Vector2f sourcePos){
	FMOD_VECTOR  listenervel = { listenerVel.x, 0.0f, listenerVel.y };
	//update position & velocity of listener
	//position of listener needed for spatial & reverb effects
	//velocity of listener needed for dopper effects
	FMOD_VECTOR  listenerpos = { listenerPos.x, 0.0f, listenerPos.y };
	//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
	m_system->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
	//update position of sound
	if (m_spatialChannel){
		FMOD_VECTOR  sourcePosition = { sourcePos.x, 0.0f, sourcePos.y };
		//source is fixed so velocity is zero
		m_spatialChannel->set3DAttributes(&sourcePosition, 0);
		m_spatialChannel->set3DMinMaxDistance(50, 8000);
	}
	/*FMOD::Reverb *reverb;
	m_system->createReverb(&reverb);
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
	reverb->setProperties(&prop);
	FMOD_VECTOR pos = { sourcePos.x, 0.0f, sourcePos.y };
	float mindist = 100.0f;
	float maxdist = 150.0f;
	reverb->set3DAttributes(&pos, mindist, maxdist);

	reverb->setActive(true);*/
	m_system->update();
}

void SoundManager::muteEffects(){
	m_effectsMute = !m_effectsMute;
}

void SoundManager::muteMusic(){
	m_musicMute = !m_musicMute;
	m_musicChannel->setMute(m_musicMute);
}