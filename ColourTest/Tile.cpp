#include "Tile.h"
#include <iostream>

Tile::Tile(){

}

Tile::Tile(int x, int y, float size, sf::Color col, sf::Sprite sprite ) : m_pos(sf::Vector2f(x, y)), m_size(size), m_col(col), m_used(false), m_sprite(sprite) {
	m_shape = sf::RectangleShape(sf::Vector2f(m_size, m_size));
	m_shape.setPosition(m_pos);
	m_shape.setFillColor(m_col);
	
	m_sprite.setPosition(m_pos);
	m_texWidth = m_sprite.getGlobalBounds().width / 3;
	float scale = size / m_texWidth;
	m_sprite.setTextureRect(sf::IntRect(m_texWidth, m_texWidth, m_texWidth, m_texWidth));

	m_sprite.setScale(scale, scale);

	m_enterDir = Direction::NONE;
	m_exitDir = Direction::NONE;
}

Tile::Tile(int x, int y, float size, sf::Color above, sf::Color left, sf::Sprite sprite) : 
	m_pos(sf::Vector2f(x, y)), 
	m_size(size), m_used(false) , 
	m_sprite(sprite) {
	m_col = above;
	while (m_col == above || m_col == left){
		int random = rand() % 8;
		if (random == 0){
			m_col = sf::Color::Red;
		}
		if (random == 1){
			m_col = sf::Color::Green;
		}
		if (random == 2){
			m_col = sf::Color::Blue;
		}
		if (random == 3){
			m_col = sf::Color::Cyan;
		}
		if (random == 4){
			m_col = sf::Color::Magenta;
		}
		if (random == 5){
			m_col = sf::Color::Yellow;
		}
		if (random == 6){
			m_col = sf::Color::Black;
		}
		if (random == 7){
			m_col = sf::Color::White;
		}
	}
	m_shape = sf::RectangleShape(sf::Vector2f(m_size, m_size));
	m_shape.setPosition(m_pos);
	m_shape.setFillColor(m_col);

	m_originalCol = m_col;
	m_sprite.setPosition(m_pos);
	m_texWidth = m_sprite.getGlobalBounds().width / 3;
	float scale = ceil(size) / m_texWidth;
	m_sprite.setTextureRect(sf::IntRect(m_texWidth, m_texWidth, m_texWidth, m_texWidth));

	m_sprite.setScale(scale, scale);
	m_enterDir = Direction::NONE;
	m_exitDir = Direction::NONE;
}

void Tile::draw(sf::RenderWindow * window) const{
	
	window->draw(m_shape);
	window->draw(m_sprite);
	for (int  i = 0; i < m_walls.size(); i++)
	{
		m_walls[i].draw(window);
	}
}

sf::Color Tile::getColour() const{
	return m_col;
}

bool Tile::getUsed() const{
	return m_used;
}

bool Tile::getChecked() const{
	return m_floodChecked;
}

int Tile::getWallCount() const{
	return m_walls.size();
}

sf::Vector2f Tile::getPos() const{
	return m_pos;
}

bool Tile::getHasPowerUp() const{
	return m_hasPowerUp;
}

bool Tile::checkWall(Direction dir) const{
	for (int i = 0; i < m_walls.size(); i++)
	{
		if (m_walls[i].getDir() == dir){
			return true;
		}
	}
	return false;
}

void Tile::setColour(sf::Color col){
	m_col = col;
	m_shape.setFillColor(col);
}

void Tile::setUsed(bool arg){
	m_used = arg;
}

void Tile::setChecked(bool arg){
	m_floodChecked = arg;
}

void Tile::setEnterDirection(Direction arg) {
	m_enterDir = arg;
	switch (arg) {
	case Direction::UP :
		m_sprite.setTextureRect(sf::IntRect(m_texWidth, m_texWidth * 4, m_texWidth, m_texWidth));
		break;
	case Direction::LEFT:
		m_sprite.setTextureRect(sf::IntRect(m_texWidth, m_texWidth * 3, m_texWidth, m_texWidth));
		break;
	case Direction::DOWN:
		m_sprite.setTextureRect(sf::IntRect(0, m_texWidth * 4, m_texWidth, m_texWidth));
		break;
	case Direction::RIGHT:
		m_sprite.setTextureRect(sf::IntRect(0, m_texWidth * 3, m_texWidth, m_texWidth));
		break;
	}
}

void Tile::setExitDirection(Direction arg) {
	m_exitDir = arg;
	if (m_enterDir == Direction::UP) {
		if (m_exitDir == Direction::LEFT) 
			m_sprite.setTextureRect(sf::IntRect(m_texWidth * 2, m_texWidth * 2, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::DOWN)
			m_sprite.setTextureRect(sf::IntRect(0, m_texWidth, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::RIGHT)
			m_sprite.setTextureRect(sf::IntRect(0, m_texWidth * 2, m_texWidth, m_texWidth));
	}
	else if (m_enterDir == Direction::LEFT) {
		if (m_exitDir == Direction::DOWN)
			m_sprite.setTextureRect(sf::IntRect(m_texWidth * 2, 0, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::RIGHT)
			m_sprite.setTextureRect(sf::IntRect(m_texWidth, 0, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::UP)
			m_sprite.setTextureRect(sf::IntRect(m_texWidth * 2, m_texWidth * 2, m_texWidth, m_texWidth));
	}
	else if (m_enterDir == Direction::DOWN) {
		if (m_exitDir == Direction::RIGHT)
			m_sprite.setTextureRect(sf::IntRect(0, 0, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::UP)
			m_sprite.setTextureRect(sf::IntRect(0, m_texWidth, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::LEFT)
			m_sprite.setTextureRect(sf::IntRect(m_texWidth * 2, 0, m_texWidth, m_texWidth));
	}
	else if (m_enterDir == Direction::RIGHT) {
		if (m_exitDir == Direction::UP)
			m_sprite.setTextureRect(sf::IntRect(0, m_texWidth * 2, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::LEFT)
			m_sprite.setTextureRect(sf::IntRect(m_texWidth, 0, m_texWidth, m_texWidth));

		else if (m_exitDir == Direction::DOWN)
			m_sprite.setTextureRect(sf::IntRect(0, 0, m_texWidth, m_texWidth));
	}
}

void Tile::setHasPowerUp(bool arg){
	m_hasPowerUp = arg;
}

void Tile::addWalls(Direction direction){
	m_walls.push_back(Wall(direction, m_pos, m_size));
}

void Tile::reset(bool col){
	if (col){
		m_col = m_originalCol;
		m_shape.setFillColor(m_col);
	}
	m_used = false;
	m_enterDir = Direction::NONE;
	m_enterDir = Direction::NONE;

	m_sprite.setTextureRect(sf::IntRect(m_texWidth, m_texWidth, m_texWidth, m_texWidth));
}