#include "stdafx.h"
#include "SoundManager.h"

SoundManager * SoundManager::m_instance = nullptr;

SoundManager::SoundManager(){
	FMOD_RESULT result;
	m_fmodisloaded = true;
	result = FMOD::System_Create(&m_system);         // Create the main system object.
	if (result != FMOD_OK)	{
		m_fmodisloaded = false;
	}
	result = m_system->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
	if (result != FMOD_OK){;
		
		m_fmodisloaded = false;
	}

	// effects
	FMOD::Sound * audio;
	result = m_system->createSound("res/sounds/button.wav", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){

		m_fmodisloaded = false;
	}
	m_effects.push_back(audio);

	result = m_system->createSound("res/sounds/success.wav", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){

		m_fmodisloaded = false;
	}
	m_effects.push_back(audio);

	// music
	result = m_system->createSound("res/sounds/gameMusic.mp3", FMOD_DEFAULT, 0, &audio);
	if (result != FMOD_OK){

		m_fmodisloaded = false;
	}
	m_music.push_back(audio);

	// spatial
	result = m_system->createSound("res/sounds/gong.wav", FMOD_LOOP_NORMAL | FMOD_3D, 0, &audio);
	if (result != FMOD_OK){

		m_fmodisloaded = false;
	}
	m_spatial.push_back(audio);
	//need this for sound fall off
	//m_musicChannel->setChannelGroup(channelMusic);
	//m_effectsChannel->setChannelGroup(channelEffects);
	
	m_prop = FMOD_PRESET_SEWERPIPE;
	m_spatialMute = false;
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
	if (m_fmodisloaded) {
		if (!m_effectsMute){
			if (i >= 0 && i < m_effects.size())
				m_system->playSound(FMOD_CHANNEL_FREE, m_effects[i], false, &m_effectsChannel);
		}
	}
}

void SoundManager::playMusic(int i){
	if (m_fmodisloaded) {
		if (i >= 0 && i < m_music.size()){
			//m_musicChannel->setPaused(false);
			m_system->playSound(FMOD_CHANNEL_FREE, m_music[i], false, &m_musicChannel);
			m_musicChannel->setMode(FMOD_LOOP_NORMAL);
			m_musicChannel->setLoopCount(-1);
			m_musicChannel->setVolume(0.1f);
		}
	}
}

void SoundManager::playSpatial(int i){
	if (m_fmodisloaded) {
		if (i >= 0 && i < m_spatial.size()){

			//m_musicChannel->setPaused(false);
			m_system->playSound(FMOD_CHANNEL_FREE, m_spatial[i], false, &m_spatialChannel);
			m_spatialChannel->setMode(FMOD_LOOP_NORMAL | FMOD_3D);
			m_spatialChannel->setLoopCount(-1);
		}
	}
}

void SoundManager::stopSpatial(){
	if (m_fmodisloaded) {
		m_spatialChannel->stop();
	}
}

void SoundManager::initSpatial(sf::Vector2f sourcePos){
	if (m_fmodisloaded) {
		if (m_spatialChannel){
			FMOD_VECTOR  sourcePosition = { sourcePos.x, 0.0f, sourcePos.y };
			//source is fixed so velocity is zero
			m_spatialChannel->set3DAttributes(&sourcePosition, 0);
			m_spatialChannel->set3DMinMaxDistance(50, 8000);
			/*FMOD::ChannelGroup * temp;
			m_system->createChannelGroup(NULL, &temp);
			m_spatialChannel->setChannelGroup(temp);
			temp->setPitch(1.0f);*/
		}
		m_system->createReverb(&m_reverb);
		//FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_SEWERPIPE;
		m_reverb->setProperties(&m_prop);
		FMOD_VECTOR pos = { sourcePos.x, 0.0f, sourcePos.y };
		float mindist = 100.0f;
		float maxdist = 600.0f;
		m_reverb->set3DAttributes(&pos, mindist, maxdist);

		m_reverb->setActive(m_effectsMute);

		m_system->update();
	}
}

void SoundManager::updateSpatial(sf::Vector2f listenerPos, sf::Vector2f listenerVel){
	if (m_fmodisloaded) {
		FMOD_VECTOR  listenervel = { listenerVel.x, 0.0f, listenerVel.y };
		//update position & velocity of listener
		//position of listener needed for spatial & reverb effects
		//velocity of listener needed for dopper effects
		FMOD_VECTOR  listenerpos = { listenerPos.x, 0.0f, listenerPos.y };
		//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
		FMOD_VECTOR forward = { listenerVel.x, 0.0f, -listenerVel.y };

		m_system->set3DListenerAttributes(0, &listenerpos, &listenervel, &forward, 0);

		m_system->update();
	}
}

void SoundManager::updateReverb(FMOD_REVERB_PROPERTIES p){
	if (m_fmodisloaded) {
		m_prop = p;
		m_reverb->setProperties(&m_prop);
	}
}

void SoundManager::muteEffects(){
	if (m_fmodisloaded) {
		m_effectsMute = !m_effectsMute;
	}
}

void SoundManager::muteMusic(){
	if (m_fmodisloaded) {
		m_musicMute = !m_musicMute;
		m_musicChannel->setMute(m_musicMute);
	}
}

void SoundManager::muteSpatial(){
	if (m_fmodisloaded) {
		m_spatialMute = !m_spatialMute;
		m_spatialChannel->setMute(m_spatialMute);
	}
}

void SoundManager::muteReverb(){
	if (m_fmodisloaded) {
		m_reverbMute = !m_reverbMute;
		m_reverb->setActive(m_reverbMute);
	}
}