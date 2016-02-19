#include "RainDrop.h"

RainDrop::RainDrop(sf::Sprite spr) : m_sprite(spr), m_alive(true){
	sf::Vector2f targetPos(rand() % 1800 - 500, rand() % 500);
	m_lifeCounter = targetPos.y / 16 + 1;
	m_pos = targetPos - (static_cast<float>(m_lifeCounter) * sf::Vector2f(-8, 16));
	m_sprite.setPosition(m_pos);
	m_sprite.setTextureRect(sf::IntRect(0, 8, 8, 16));
	m_sprite.setScale(2, 2);
}

void RainDrop::update(){
	m_pos += sf::Vector2f(-8, 16);
	m_sprite.setPosition(m_pos);
	m_lifeCounter--;
	if (m_lifeCounter == 0) {
		m_alive = false;
	}
}

void RainDrop::draw(sf::RenderWindow* window){
	window->draw(m_sprite);
}

bool RainDrop::getAlive() const{
	return m_alive;
}