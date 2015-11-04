#include "Tile.h"
#include <iostream>

Tile::Tile(){

}

Tile::Tile(int x, int y, int size, sf::Color col) : m_pos(sf::Vector2f(x, y)), m_size(size), m_col(col), m_used(false) {
}

Tile::Tile(int x, int y, int size, sf::Color above, sf::Color left) : m_pos(sf::Vector2f(x, y)), m_size(size), m_used(false) {
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
	m_originalCol = m_col;
}

sf::RectangleShape Tile::getDraw() const{
	sf::RectangleShape r(sf::Vector2f(m_size, m_size));
	r.setPosition(m_pos);
	r.setFillColor(m_col);
	return r;
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

void Tile::setColour(sf::Color col){
	m_col = col;
}

void Tile::setUsed(bool arg){
	m_used = arg;
}

void Tile::setChecked(bool arg){
	m_floodChecked = arg;
}

void Tile::reset(){
	m_col = m_originalCol;
	m_used = false;
}