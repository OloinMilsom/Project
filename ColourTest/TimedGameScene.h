#ifndef TIMEDGAMESCENE_H
#define TIMEDGAMESCENE_H

#include "Scene.h"
#include "Player.h"
#include "RainDrop.h"
#include <sstream>

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
	int m_score;
	Player * m_player;
	sf::Clock m_deltaClock;

	sf::RectangleShape m_finishColour;
	sf::RectangleShape m_playerColour;
	std::vector<sf::RectangleShape> m_splitPlayer;
	std::vector<sf::RectangleShape> m_splitFinish;

	sf::Sprite m_overlay;
	sf::Sprite m_ui;
	sf::Text m_scoreLabel;
	sf::Text m_timerLabel;
	sf::Text m_playerLabel;
	sf::Text m_finishLabel;
	sf::Text m_powerUpLabel;
	sf::Sprite m_raindropSprite;
	std::vector<RainDrop> m_raindrops;

	void nextRoom();
	void resetRoom();
	void checkWin();
	void xboxControls();
	void keyboardControls(sf::Event* e, sf::RenderWindow* window);
};

#endif // !TIMEDGAMESCENE_H
