#include "PowerUp.h"

PowerUp::PowerUp(float size, sf::Vector2f position, sf::Vector2f coords) : m_shape(size), m_pos(position), m_tileCoords(coords){
	m_shape.setPosition(position);
	m_shape.setFillColor(sf::Color::Yellow);
	m_type = static_cast<Type>(rand() % 1);
}

void PowerUp::draw(sf::RenderWindow * window) const{
	if (!m_active)
		window->draw(m_shape);
}

bool PowerUp::isSteppedOn(int x, int y){
	return m_tileCoords.x == x && m_tileCoords.y == y;
}

PowerUp::Type PowerUp::getType(){
	return m_type;
}

bool PowerUp::getActive(){
	return m_active;
}

void PowerUp::setActive(bool arg){
	m_active = arg;
}
