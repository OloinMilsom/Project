#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "stdafx.h"
#include "Scene.h"

class MenuScene : public Scene{
public:
	MenuScene();
	~MenuScene();
	void update(sf::Event* e);
	void draw(sf::RenderWindow* window);

private:

};

#endif