#ifndef WALL_H
#define WALL_H

#include "stdafx.h"
#include "Direction.h"

class Wall {
public:
	Wall(Direction dir = Direction::UP, sf::Vector2f pos = sf::Vector2f(0, 0), int size = 0);
	void draw(sf::RenderWindow * window) const;
	Direction getDir() const;
private:
	Direction m_dir;
	sf::Vector2f m_pos;
	int m_size;
	sf::RectangleShape m_shape;
};

#endif