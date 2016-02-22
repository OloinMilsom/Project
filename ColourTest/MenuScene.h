#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

class MenuScene : public Scene{
public:
	MenuScene(sf::Font* font);
	~MenuScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();

private:

	sf::Sprite m_sprBackground;
	sf::Texture * m_backgroundTex;
	sf::Sprite m_title;
	sf::Texture * m_titleTex;
};

#endif