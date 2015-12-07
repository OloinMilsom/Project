#include "Wall.h"

Wall::Wall(Direction dir, sf::Vector2f pos, int size) :
		m_dir(dir),
		m_pos(pos),
		m_size(size)
{
	switch (dir){
	case Direction::UP:
		m_shape = sf::RectangleShape(sf::Vector2f(size, size / 8));
		m_shape.setPosition(pos + sf::Vector2f(0, -size / 16));
		break;
	case Direction::LEFT:
		m_shape = sf::RectangleShape(sf::Vector2f(size / 8, size));
		m_shape.setPosition(pos + sf::Vector2f(-size / 16, 0));
		break;
	case Direction::DOWN:
		m_shape = sf::RectangleShape(sf::Vector2f(size, size / 8));
		m_shape.setPosition(pos + sf::Vector2f(0, size - size / 16));
		break;
	case Direction::RIGHT:
		m_shape = sf::RectangleShape(sf::Vector2f(size / 8, size));
		m_shape.setPosition(pos + sf::Vector2f(size - size / 16, 0));
		break;
	}
	m_shape.setFillColor(sf::Color(100, 149, 237));
}

void Wall::draw(sf::RenderWindow * window) const{
	window->draw(m_shape);
}