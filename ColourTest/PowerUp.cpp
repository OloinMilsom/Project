#include "PowerUp.h"

PowerUp::PowerUp(float size, sf::Vector2f position, sf::Vector2f coords, sf::Vector2f moveTo) : m_shape(size), m_pos(position), m_tileCoords(coords), m_moveTo(moveTo), m_initialPos(position){
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getGlobalBounds().width / 2, m_shape.getGlobalBounds().height / 2);
	m_shape.setFillColor(sf::Color::Yellow);
	m_type = static_cast<Type>(rand() % 1);
	m_moving = false;
	m_active = false;
}

void PowerUp::draw(sf::RenderWindow * window) const{
	if (!m_active || m_moving)
		window->draw(m_shape);
	if (!m_particles.empty()) {
		for (std::vector<std::pair<sf::CircleShape, sf::Vector2f>>::const_iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
		{
			window->draw(iter->first);
		}
	}
}

void PowerUp::update(){
	if (m_moving && m_pos.x > m_moveTo.x - 10 && m_pos.x < m_moveTo.x + 10 &&
		m_pos.y > m_moveTo.y - 10 && m_pos.y < m_moveTo.y + 10){
		m_moving = false;
		m_exploding = true;
		makeParticles();
		m_pos = m_moveTo;
		m_shape.setPosition(m_pos);
	}
	if (m_moving){
		m_vel.y += 0.25f;
		m_pos += m_vel;
		m_shape.setPosition(m_pos);
	}
	if (m_exploding){
		for (std::vector<std::pair<sf::CircleShape, sf::Vector2f>>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
		{
			sf::Vector2f pos = iter->first.getPosition();
			pos += iter->second;
			iter->first.setPosition(pos);
			if ((pos.x - m_moveTo.x) * (pos.x - m_moveTo.x) + (pos.y - m_moveTo.y) * (pos.y - m_moveTo.y) > 12500){
				m_particles.erase(iter);
				break;
			}
		}
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
	float time = 30;
	m_vel.x = -(m_pos.x - m_moveTo.x) / time;
	float yDist = m_pos.y - m_moveTo.y;
	m_vel.y = (-yDist - 0.5f * (0.25f) * (time * time)) / time;
}

void PowerUp::reset(){
	m_active = false;
	m_moving = false;
	m_exploding = false;
	m_pos = m_initialPos;
	m_shape.setPosition(m_pos);
}

void PowerUp::makeParticles(){
	for (int i = 0; i < 20; i++)
	{
		sf::CircleShape s(2);
		s.setFillColor(sf::Color::Yellow);
		s.setPosition(m_moveTo);

		sf::Vector2f v(rand() % 9 - 4, rand() % 9 - 4);
		if (v == sf::Vector2f(0, 0))
			v.x = 1;
		m_particles.push_back(std::make_pair(s, v));
	}
}
