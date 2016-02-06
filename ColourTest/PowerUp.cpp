#include "PowerUp.h"

PowerUp::PowerUp(float size, sf::Vector2f position, sf::Vector2f coords) : m_shape(size), m_pos(position), m_tileCoords(coords){
	m_shape.setPosition(position);
	m_shape.setFillColor(sf::Color::Yellow);
}

void PowerUp::draw(sf::RenderWindow * window) const{
	window->draw(m_shape);
}

bool PowerUp::isSteppedOn(int x, int y){
	return m_tileCoords.x == x && m_tileCoords.y == y;
}