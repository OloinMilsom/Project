#ifndef PAUSESCENE_H
#define PAUSESCENE_H

#include "Scene.h"

class PauseScene : public Scene{
public:
	PauseScene(sf::Font* font);
	~PauseScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void setFrom(SceneID from);
	void stop();

private:
	SceneID cameFrom;
	sf::Sprite m_sprBackground;
};

#endif