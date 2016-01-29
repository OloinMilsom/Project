#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "Scene.h"

class OptionsScene : public Scene{
public:
	OptionsScene(sf::Font* font);
	~OptionsScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();

private:

	sf::Sprite m_sprBackground;
};

#endif