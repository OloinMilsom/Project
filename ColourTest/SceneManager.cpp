#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "TimedGameScene.h"
#include "OptionsScene.h"
#include "AchievementsScene.h"
#include "PauseScene.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager(){
	m_currentID = SceneID::MENU;
	m_font.loadFromFile("C:\\Windows\\Fonts\\Arial.TTF");
	m_scenes.push_back(new MenuScene(&m_font));
	m_scenes.push_back(new GameScene(&m_font));
	m_scenes.push_back(new TimedGameScene(&m_font));
	m_scenes.push_back(new GameOverScene(&m_font, "You Lose!", SceneID::GAME));
	m_scenes.push_back(new GameOverScene(&m_font, "You Win!", SceneID::GAME));
	m_scenes.push_back(new GameOverScene(&m_font, "Time's up!", SceneID::TIMEDGAME));
	m_scenes.push_back(new OptionsScene(&m_font));
	m_scenes.push_back(new AchievementsScene(&m_font));
	m_scenes.push_back(new PauseScene(&m_font));
}

SceneManager* SceneManager::getInstance(){
	if (m_instance == nullptr)
	{
		m_instance = new SceneManager();
	}
	return m_instance;
}

SceneManager::~SceneManager(){
	if (!m_scenes.empty()){
		for (int i = 0; i < m_scenes.size(); i++)
		{
			delete m_scenes[i];
		}
		m_scenes.clear();
	}
}

void SceneManager::update(sf::Event* e, sf::RenderWindow* window){
	m_scenes[static_cast<int>(m_currentID)]->update(e, window);
}

void SceneManager::draw(sf::RenderWindow* window){
	m_scenes[static_cast<int>(m_currentID)]->draw(window);
}

void SceneManager::goToScene(SceneID goTo){
	m_scenes[static_cast<int>(m_currentID)]->stop();
	m_currentID = goTo;
	m_scenes[static_cast<int>(m_currentID)]->start();
}

void SceneManager::goToPause(SceneID from){
	m_currentID = SceneID::PAUSE;
	m_scenes[static_cast<int>(SceneID::PAUSE)]->start();
	dynamic_cast<PauseScene *>(m_scenes[static_cast<int>(SceneID::PAUSE)])->setFrom(from);
}

void SceneManager::stopScene(SceneID stop){
	m_scenes[static_cast<int>(stop)]->stop();
}