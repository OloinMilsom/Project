#include "Wall.h"

Wall::Wall(Direction dir, sf::Vector2f pos, float size, sf::Sprite spr) :
		m_dir(dir),
		m_pos(pos),
		m_size(size),
		m_sprite(spr)
{
	switch (dir){
	case Direction::UP:
		m_sprite.setTextureRect(sf::IntRect(48, 240, 48, 8));
		m_sprite.setScale(size / 48, size / 48);
		m_sprite.setPosition(pos + sf::Vector2f(0, -size / 12));
		break;
	case Direction::LEFT:
		m_sprite.setTextureRect(sf::IntRect(0, 240, 6, 48));
		m_sprite.setScale(size / 48, size / 48);
		m_sprite.setPosition(pos + sf::Vector2f(-size / 16, 0));
		break;
	case Direction::DOWN:
		m_sprite.setTextureRect(sf::IntRect(48, 240, 48, 8));
		m_sprite.setScale(size / 48, size / 48);
		m_sprite.setPosition(pos + sf::Vector2f(0, size - size / 12 ));
		break;
	case Direction::RIGHT:
		m_sprite.setTextureRect(sf::IntRect(0, 240, 6, 48));
		m_sprite.setScale(size / 48, size / 48);
		m_sprite.setPosition(pos + sf::Vector2f(size-size / 16, 0));
		break;
	}
}

void Wall::draw(sf::RenderWindow * window) const{
	window->draw(m_sprite);
}

Direction Wall::getDir() const{
	return m_dir;
}
