#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"

class GameScene : public Scene{
public:
	GameScene(sf::Font* font);
	~GameScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();
private:
	int m_currSize;
	int m_attempts;
	Player * m_player;
};

#endif