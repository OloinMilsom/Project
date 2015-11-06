#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Button.h"

class Scene {
protected:
	std::vector<Button> m_buttons;
public:
	Scene();
	virtual ~Scene();
	void virtual update(sf::Event* e) = 0;
	void virtual draw(sf::RenderWindow* window) = 0;
};

#endif