#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"

class GameScene : public Scene{
public:
	GameScene();
	~GameScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
private:
	int m_currSize;
	Player * m_player;// = new Player(0, TileManager::getInstance()->getSize() / 2);
};

#endif