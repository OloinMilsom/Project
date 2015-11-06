#include "SceneManager.h"
#include "GameScene.h"

SceneManager* SceneManager::m_instance = nullptr;

SceneManager::SceneManager(){
	m_currentID = SceneID::GAME;
	m_scenes.push_back(new GameScene());
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

void SceneManager::update(sf::Event* e){
	m_scenes[static_cast<int>(m_currentID)]->update(e);
}

void SceneManager::draw(sf::RenderWindow* window){
	m_scenes[static_cast<int>(m_currentID)]->draw(window);
}