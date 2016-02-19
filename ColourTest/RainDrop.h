#ifndef RAINDROP_H
#define RAINDROP_H

#include "stdafx.h"

class RainDrop {
public:
	RainDrop(sf::Sprite spr);
	void update();
	void draw(sf::RenderWindow* window);
	bool getAlive() const;
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;
	int m_lifeCounter;
	bool m_alive;

};

#endif