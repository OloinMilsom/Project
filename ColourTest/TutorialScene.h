#ifndef TUTORIALSCENE_H
#define TUTORIALSCENE_H

#include "Scene.h"

class TutorialScene : public Scene{
public:
	TutorialScene(sf::Font* font);
	~TutorialScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();

private:
	sf::Sprite m_sprBackground;
};

#endif