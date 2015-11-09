#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include <vector>
#include "SceneID.h"

class Scene;

class SceneManager{
public:
	static SceneManager* getInstance();
	~SceneManager();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void goToScene(SceneID goTo);
private:
	SceneManager();
	SceneID m_currentID;
	std::vector<Scene*> m_scenes;
	static SceneManager* m_instance;
	sf::Font m_font;
};

#endif // !SCENEMANAGER_H
