#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "stdafx.h"
#include "Scene.h"
#include "Player.h"

class GameScene : public Scene{
public:
	GameScene();
	~GameScene();
	void update(sf::Event* e);
	void draw(sf::RenderWindow* window);
private:

	Player * player;// = new Player(0, TileManager::getInstance()->getSize() / 2);
};

#endif