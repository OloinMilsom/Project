#include "Player.h"
#include <iostream>

Player::Player(){

}

Player::Player(int x, int y){
	m_pos = sf::Vector2f(x, y);
	//int t = m_colourDevision;
}

sf::Color Player::getColour() const{
	return sf::Color(m_red * 255 / m_colourDevision, m_green * 255 / m_colourDevision, m_blue * 255 / m_colourDevision);
}

sf::Vector2f Player::getPos() const{
	return m_pos;
}

void Player::setPos(sf::Vector2f pos){
	m_pos = pos;
}

void Player::resetColour(){
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

void Player::addColour(sf::Color c){

	// RED
	if (c == sf::Color::Red){
		if (m_red < m_colourDevision){
			m_red+=2;
		}
		else {
			if (m_green > 0)
				m_green--;
			if (m_blue > 0)
				m_blue--;
		}
	}

	// GREEN
	if (c == sf::Color::Green){
		if (m_green < m_colourDevision){
			m_green += 2;
		}
		else {
			if (m_red > 0)
				m_red--;
			if (m_blue > 0)
				m_blue--;
		}
	}

	// BLUE
	if (c == sf::Color::Blue){
		if (m_blue < m_colourDevision){
			m_blue += 2;
		}
		else {
			if (m_green > 0)
				m_green--;
			if (m_red > 0)
				m_red--;
		}
	}

	// CYAN
	if (c == sf::Color::Cyan){
		if (m_blue < m_colourDevision){
			m_blue++;
		}
		if (m_green < m_colourDevision){
			m_green++;
		}
		if (m_blue >= m_colourDevision || m_green >= m_colourDevision){
			if (m_red > 0)
				m_red -= 2;
		}
	}

	// MAGENTA
	if (c == sf::Color::Magenta){
		if (m_blue < m_colourDevision){
			m_blue++;
		}
		if (m_red < m_colourDevision){
			m_red++;
		}
		if (m_blue >= m_colourDevision || m_red >= m_colourDevision){
			if (m_green > 0)
				m_green -= 2;
		}
	}

	// YELLOW
	if (c == sf::Color::Yellow){
		if (m_red < m_colourDevision){
			m_red++;
		}
		if (m_green < m_colourDevision){
			m_green++;
		}
		if (m_red >= m_colourDevision || m_green >= m_colourDevision){
			if (m_blue > 0)
				m_blue -= 2;
		}
	}

	// BLACK
	if (c == sf::Color::Black){
		if (m_red > 0){
			m_red--;
		}
		if (m_green > 0){
			m_green--;
		}
		if (m_blue > 0){
			m_blue--;
		}
	}

	// WHITE
	if (c == sf::Color::White){
		if (m_red < m_colourDevision){
			m_red++;
		}
		if (m_green < m_colourDevision){
			m_green++;
		}
		if (m_blue < m_colourDevision){
			m_blue++;
		}
	}
	if (m_red > m_colourDevision)
	{
		m_red = m_colourDevision;
	}
	if (m_green > m_colourDevision)
	{
		m_green = m_colourDevision;
	}
	if (m_blue > m_colourDevision)
	{
		m_blue = m_colourDevision;
	}
	if (m_red < 0)
	{
		m_red = 0;
	}
	if (m_green < 0)
	{
		m_green = 0;
	}
	if (m_blue < 0)
	{
		m_blue = 0;
	}
	std::cout << "Red: " << m_red << "\t" << "Green: " << m_green << "\t" << "Blue: " << m_blue << "\t" << std::endl;
}

void Player::move(Player::direction d){
	switch (d){
	case direction::UP:
		if (m_pos.x != -1 && m_pos.y > 0 && !TileManager::getInstance()->at(m_pos.x, m_pos.y - 1)->getUsed()){
			m_pos.y -= 1;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
			TileManager::getInstance()->setUsedColour(getColour());
		}
		break;
	case direction::LEFT:
		if (m_pos.x > 0 && !TileManager::getInstance()->at(m_pos.x - 1, m_pos.y)->getUsed()){
			m_pos.x -= 1;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
			TileManager::getInstance()->setUsedColour(getColour());
		}
		break;
	case direction::DOWN:
		if (m_pos.x != -1 && m_pos.y < TileManager::getInstance()->getSize() - 1 && !TileManager::getInstance()->at(m_pos.x, m_pos.y + 1)->getUsed()){
			m_pos.y += 1;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
			TileManager::getInstance()->setUsedColour(getColour());
		}
		break;
	case direction::RIGHT:
		if (m_pos.x < TileManager::getInstance()->getSize() - 1 && !TileManager::getInstance()->at(m_pos.x + 1, m_pos.y)->getUsed()){
			m_pos.x += 1;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
			TileManager::getInstance()->setUsedColour(getColour());
		}
		else if (m_pos.x == TileManager::getInstance()->getSize() - 1 && m_pos.y == TileManager::getInstance()->getSize() / 2 &&
			getColour() == TileManager::getInstance()->getFinishColor()){
			m_pos.x += 1;
		}
		break;
	}
}

void Player::goalFinder(){
	// size of the room
	int size = TileManager::getInstance()->getSize();
	// position of the final tile
	sf::Vector2f finalPos(size - 1, size / 2);
	// add the fist colour
	addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
	// set the first tile to be used
	TileManager::getInstance()->setUsed(m_pos);
	
	// while not on the final tile
	while (!(m_pos.x == finalPos.x && m_pos.y == finalPos.y)){
		// choose a random direction
		int random = rand() % 4;
		// left
		if (random == 0 && m_pos.x > 0 && !TileManager::getInstance()->at(m_pos.x - 1, m_pos.y)->getUsed() && 
			TileManager::getInstance()->floodFillCheck(m_pos.x - 1, m_pos.y, finalPos.x, finalPos.y)){
			m_pos.x--;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		// up
		else if (random == 1 && m_pos.y > 0 && !TileManager::getInstance()->at(m_pos.x , m_pos.y - 1)->getUsed() &&
			TileManager::getInstance()->floodFillCheck(m_pos.x, m_pos.y - 1, finalPos.x, finalPos.y)){
			m_pos.y--;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		//right
		else if (random == 2 && m_pos.x < size - 1 && !TileManager::getInstance()->at(m_pos.x + 1, m_pos.y)->getUsed() &&
			TileManager::getInstance()->floodFillCheck(m_pos.x + 1, m_pos.y, finalPos.x, finalPos.y)){
			m_pos.x++;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		// down
		else if (random == 3 && m_pos.y < size - 1 && !TileManager::getInstance()->at(m_pos.x, m_pos.y + 1)->getUsed() &&
			TileManager::getInstance()->floodFillCheck(m_pos.x, m_pos.y + 1, finalPos.x, finalPos.y)){
			m_pos.y++;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		TileManager::getInstance()->resetChecked();
	}
	// set final colour
	TileManager::getInstance()->setFinalColour(getColour());
	// reset all the used tiles
	TileManager::getInstance()->resetUsed();
	// set the player position
	m_pos.x = -1;
	// reset the player colour
	m_red = m_green = m_blue = 0;
}



