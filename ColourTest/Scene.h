#ifndef SCENE_H
#define SCENE_H

#include "Button.h"
#include <vector>

class Button;

class Scene {
protected:
	std::vector<Button> m_buttons;
public:
	Scene();
	virtual ~Scene();
	void virtual update(sf::Event* e, sf::RenderWindow* window) = 0;
	void virtual draw(sf::RenderWindow* window) = 0;
	void virtual start() = 0;
	void virtual stop() = 0;
};

#endif