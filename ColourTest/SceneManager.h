#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"
#include <vector>
#include "Scene.h"
#include "GameScene.h"

class SceneManager{
private:
	SceneManager();
	enum class SceneID{
		GAME
	};
	SceneID m_currentID;
	std::vector<Scene*> m_scenes;
	static SceneManager* m_instance;
public:
	static SceneManager* getInstance();
	~SceneManager();
	void update(sf::Event* e);
	void draw(sf::RenderWindow* window);

};

#endif // !SCENEMANAGER_H
