#include "stdafx.h"
#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f dims, SceneID goTo, std::string title, sf::Font* font)
: m_position(pos), 
  m_dimensions(dims),
  m_goTo(goTo) {
	m_title.setFont(*font);
	m_title.setString(title);
	m_title.setCharacterSize(24);
	m_title.setColor(sf::Color::Blue);
	m_title.setStyle(sf::Text::Bold);
	m_title.setPosition(m_position.x + 20, m_position.y + 8);
}

void Button::isClicked(sf::Vector2f mouse){
	if (mouse.x > m_position.x && mouse.x < m_position.x + m_dimensions.x &&
		mouse.y > m_position.y && mouse.y < m_position.y + m_dimensions.y){
		SceneManager::getInstance()->goToScene(m_goTo);
	}
}

void Button::draw(sf::RenderWindow* window){
	sf::RectangleShape shape(m_dimensions);
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color::White);
	window->draw(shape);
	window->draw(m_title);
}