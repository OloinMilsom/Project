#ifndef TIMEDGAMESCENE_H
#define TIMEDGAMESCENE_H

#include "Scene.h"
#include "Player.h"

class TimedGameScene : public Scene{
public:
	TimedGameScene();
	~TimedGameScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
private:
	int m_currSize;
	int m_timer;
	Player * m_player;
};

#endif // !TIMEDGAMESCENE_H
