#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "Scene.h"
#include "TileManager.h"
#include "Player.h"
#include "RainDrop.h"

class TutorialScene : public Scene{
public:
	TutorialScene(sf::Font* font);
	~TutorialScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();

private:
	Player * m_player;
	sf::RectangleShape m_finishColour;
	sf::RectangleShape m_playerColour;
	sf::Sprite m_overlay;
	sf::Sprite m_raindropSprite;
	std::vector<RainDrop> m_raindrops;
	int m_currTutorial;
	sf::Text m_topLabel;
	sf::Text m_bottomLabel;

	void nextRoom();
	void resetRoom();
	void checkWin();
	void xboxControls();
};

#endif