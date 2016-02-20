#ifndef BUTTON_H
#define BUTTON_H

#include "stdafx.h"

class Button{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_dimensions;
	sf::Text m_title;
	bool m_selected = false;
	bool m_isPressed;
	sf::RectangleShape m_shape;
public:
	Button(sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f dims = sf::Vector2f(0.0f, 0.0f), std::string m_title = "Title", sf::Font* font = nullptr);
	// to be called when mouse is moved
	bool isMouseOver(sf::Vector2f);
	
	// to be called when mouse is pressed
	bool isClicked(sf::Vector2f);

	bool getSelected();
	void setSelected(bool);
	void draw(sf::RenderWindow * window);
	
};

#endif
