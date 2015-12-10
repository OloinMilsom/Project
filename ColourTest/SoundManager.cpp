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
	FMOD::Sound * audio;
	result = m_system->createSound("res/sounds/button.wav", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){
		exit(-1);
	}
	m_effects.push_back(audio);
	/*result = m_system->createSound("res/sounds/gameMusic.mp3", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){
		exit(-1);
	}*/
	//m_system->createChannelGroup(NULL, &channelMusic);
	//m_system->createChannelGroup(NULL, &channelEffects);
	m_system->createStream("res/sounds/gameMusic.mp3", FMOD_DEFAULT, 0, &audio);
	m_music.push_back(audio);
	
	
	m_system->playSound(FMOD_CHANNEL_FREE, m_effects[0], true, &m_effectsChannel);
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
	if (i >= 0 && i < m_effects.size())
		m_system->playSound(FMOD_CHANNEL_FREE, m_effects[i], false, &m_effectsChannel);
}

void SoundManager::playMusic(int i){
	if (i >= 0 && i < m_music.size()){
		//m_musicChannel->setPaused(false);
		m_system->playSound(FMOD_CHANNEL_FREE, m_music[0], false, &m_musicChannel);
		m_musicChannel->setMode(FMOD_LOOP_NORMAL);
		m_musicChannel->setLoopCount(-1);
	}
}