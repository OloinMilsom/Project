#ifndef TIMEDGAMESCENE_H
#define TIMEDGAMESCENE_H

#include "Scene.h"
#include "Player.h"

class TimedGameScene : public Scene{
public:
	TimedGameScene(sf::Font* font);
	~TimedGameScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();
private:
	int m_currSize;
	float m_timer;
	Player * m_player;
	sf::Clock m_deltaClock;

	void nextRoom();
	void resetRoom();
	void checkWin();
	void xboxControls();
	void keyboardControls(sf::Event* e, sf::RenderWindow* window);
};

#endif // !TIMEDGAMESCENE_H
