#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f dims) : m_position(pos), m_dimensions(dims){

}

bool Button::isClicked(sf::Vector2f mouse){
	return (mouse.x > m_position.x && mouse.x < m_position.x + m_dimensions.x &&
		mouse.y > m_position.y && mouse.y < m_position.y + m_dimensions.y);
}

void Button::draw(sf::RenderWindow* window){
	sf::RectangleShape shape(m_dimensions);
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color::Blue);
	window->draw(shape);
}