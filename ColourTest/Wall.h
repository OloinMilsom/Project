#ifndef WALL_H
#define WALL_H

#include "stdafx.h"
#include "Direction.h"

class Wall {
public:
	Wall();
	Wall(Direction dir, sf::Vector2f pos, float size, sf::Sprite spr);
	void draw(sf::RenderWindow * window) const;
	Direction getDir() const;
private:
	Direction m_dir;
	sf::Vector2f m_pos;
	int m_size;
	sf::Sprite m_sprite;
};

#endif