#include "stdafx.h"
#include "Button.h"
#include "SoundManager.h"

Button::Button(sf::Vector2f pos, sf::Vector2f dims, std::string title, sf::Font* font)
: m_position(pos),
  m_dimensions(dims){
	m_title.setFont(*font);
	m_title.setString(title);
	m_title.setCharacterSize(24);
	m_title.setColor(sf::Color::Blue);
	m_title.setStyle(sf::Text::Bold);
	m_title.setPosition(m_position.x + 20, m_position.y + 8);
	m_shape = sf::RectangleShape(dims);
	m_shape.setPosition(pos);
	m_shape.setFillColor(sf::Color(128, 128, 128));
	m_shape.setOutlineColor(sf::Color::White);
}

bool Button::isMouseOver(sf::Vector2f mouse){
	if (mouse.x > m_position.x && mouse.x < m_position.x + m_dimensions.x &&
		mouse.y > m_position.y && mouse.y < m_position.y + m_dimensions.y){
		m_selected = true;
	}
	else
	{
		m_selected = false;
	}
	return m_selected;
}

bool Button::isClicked(sf::Vector2f mouse){
	if (m_selected || (mouse.x > m_position.x && mouse.x < m_position.x + m_dimensions.x &&
		mouse.y > m_position.y && mouse.y < m_position.y + m_dimensions.y)){
		m_isPressed = true;
		SoundManager::getInstance()->playEffect(0);
	}
	else {
		m_isPressed = false;
	}
	return m_isPressed;
}

bool Button::getSelected(){
	return m_selected;
}

void Button::setSelected(bool arg){
	m_selected = arg;
}

void Button::draw(sf::RenderWindow* window){
	if (m_selected)
	{
		m_shape.setOutlineThickness(4);
	}
	else{
		m_shape.setOutlineThickness(0);
	}
	window->draw(m_shape);
	window->draw(m_title);
}