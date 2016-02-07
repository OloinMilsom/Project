#ifndef POWERUP_H
#define POWERUP_H

#include "stdafx.h"

class PowerUp {
public:
	enum Type {
		COLOURSPLIT,
		NONE
	};
	
	PowerUp(float size = 0.0f, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f coords = sf::Vector2f(0, 0));
	void draw(sf::RenderWindow * window) const;
	
	bool isSteppedOn(int x, int y);
	Type getType();
	bool getActive();

	void setActive(bool);
private:
	Type m_type;
	sf::Vector2f m_pos;
	sf::Vector2f m_tileCoords;
	sf::CircleShape m_shape;
	bool m_active;
};

#endif