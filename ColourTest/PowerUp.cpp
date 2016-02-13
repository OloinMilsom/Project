#include "PowerUp.h"

PowerUp::PowerUp(float size, sf::Vector2f position, sf::Vector2f coords) : m_shape(size), m_pos(position), m_tileCoords(coords){
	m_shape.setPosition(position);
	m_shape.setFillColor(sf::Color::Yellow);
	m_type = static_cast<Type>(rand() % 1);
}

void PowerUp::draw(sf::RenderWindow * window) const{
	if (!m_active || m_moving)
		window->draw(m_shape);
}

void PowerUp::update(){
	if (m_pos.x > 100 - 5 && m_pos.x < 100 + 5 &&
		m_pos.y > 100 - 5 && m_pos.y < 100 + 5){
		m_moving = false;
		m_pos = sf::Vector2f(100,100);
		m_shape.setPosition(m_pos);
	}
	if (m_moving){
		m_vel.y+= 0.06f;
		m_pos += m_vel;
		m_shape.setPosition(m_pos);
	}
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
	m_moving = true;
	m_vel.x = -1;
	float time = m_pos.x - 100;
	float yDist = m_pos.y - 100;
	m_vel.y = (-yDist - 0.5f * (0.06f) * (time * time)) / time;
}
