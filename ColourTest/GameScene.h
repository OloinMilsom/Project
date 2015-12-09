#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "fmod.hpp"

class GameScene : public Scene{
public:
	GameScene();
	~GameScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();
private:
	int m_currSize;
	int m_attempts;
	Player * m_player;
	FMOD::Sound *audio;
	FMOD::System * system;
};

#endif