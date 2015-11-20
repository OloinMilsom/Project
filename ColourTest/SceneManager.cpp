#include "stdafx.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "TimedGameScene.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager(){
	m_currentID = SceneID::MENU;
	m_font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	m_scenes.push_back(new MenuScene(&m_font));
	m_scenes.push_back(new GameScene());
	m_scenes.push_back(new TimedGameScene());
	m_scenes.push_back(new GameOverScene(&m_font, "You Lose!"));
	m_scenes.push_back(new GameOverScene(&m_font, "You Win!"));
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
	m_currentID = goTo;
}