#ifndef BUTTON_H
#define BUTTON_H

#include "stdafx.h"

class Button{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_dimensions;
	
public:
	Button(sf::Vector2f pos = sf::Vector2f(0,0), sf::Vector2f dims = sf::Vector2f(0.0f, 0.0f));
	bool isClicked(sf::Vector2f);
	void draw(sf::RenderWindow* window);
};

#endif // !BUTTON_H
