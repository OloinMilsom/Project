#include "Player.h"
#include <iostream>
#include "AchievementManager.h"
#include "PowerUpManager.h"

Player::Player(){

}

Player::Player(int x, int y){
	m_pos = sf::Vector2f(x, y);
	m_moving = false;
}

void Player::draw(sf::RenderWindow * window) const{
	sf::CircleShape circ((500 / TileManager::getInstance()->getSize()) * 0.25f);
	sf::CircleShape facingCirc((500 / TileManager::getInstance()->getSize()) * 0.125f);

	circ.setPosition(getWorldPos() + sf::Vector2f(circ.getRadius(), circ.getRadius()));
	facingCirc.setPosition(getWorldPos() + sf::Vector2f(circ.getRadius() * 2 + m_vel.x * facingCirc.getRadius() - facingCirc.getRadius(),
										circ.getRadius() * 2 + m_vel.y * facingCirc.getRadius() - facingCirc.getRadius()));

	circ.setFillColor(sf::Color(100, 100, 100));
	facingCirc.setFillColor(sf::Color(50, 50, 50));

	window->draw(circ);
	window->draw(facingCirc);
}

void Player::update(){
	if (m_worldPos.x > m_targetPos.x - 5 && m_worldPos.x < m_targetPos.x + 5 && 
		m_worldPos.y > m_targetPos.y - 5 && m_worldPos.y < m_targetPos.y + 5){
		m_moving = false;
		m_worldPos = m_targetPos;
	}
	if (m_moving){
		sf::Vector2f towards = m_targetPos - m_worldPos;
		float towardsLength = sqrt(towards.x * towards.x + towards.y * towards.y);
		towards /= towardsLength * 10.0f;
		m_vel += towards;
		float velLength = sqrt(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
		m_vel /= velLength;
		m_worldPos += m_vel;		
	}
}

sf::Color Player::getColour() const{
	return sf::Color(m_red * 255 / m_colourDevision, m_green * 255 / m_colourDevision, m_blue * 255 / m_colourDevision);
}

sf::Vector2f Player::getPos() const{
	return m_pos;
}

sf::Vector2f Player::getWorldPos() const{
	return m_worldPos;
}

Direction Player::getDir() const{
	return m_dir;
}

sf::Vector2f Player::getVel() const{
	return m_vel;
}

void Player::setPos(sf::Vector2f pos){
	m_pos = pos;
	m_worldPos = sf::Vector2f(m_pos.x * (500 / TileManager::getInstance()->getSize()) + 150,
		m_pos.y * (500 / TileManager::getInstance()->getSize()));
	m_targetPos = m_worldPos;
	m_moving = false;
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

bool Player::canMove(Direction dir){
	switch (dir){
	case Direction::UP:
		return !TileManager::getInstance()->checkWallAt(m_pos.x, m_pos.y, Direction::UP) &&
			!TileManager::getInstance()->at(m_pos.x, m_pos.y - 1)->getUsed();
		break;
	case Direction::LEFT:
		return !TileManager::getInstance()->checkWallAt(m_pos.x, m_pos.y, Direction::LEFT) &&
			!TileManager::getInstance()->at(m_pos.x - 1, m_pos.y)->getUsed();
		break;
	case Direction::DOWN:
		return !TileManager::getInstance()->checkWallAt(m_pos.x, m_pos.y, Direction::DOWN) &&
			!TileManager::getInstance()->at(m_pos.x, m_pos.y + 1)->getUsed();
		break;
	case Direction::RIGHT:
		return !TileManager::getInstance()->checkWallAt(m_pos.x, m_pos.y, Direction::RIGHT) &&
			!TileManager::getInstance()->at(m_pos.x + 1, m_pos.y)->getUsed();
		break;
	}
}

void Player::move(Direction d){
	if (!m_moving) {
		m_dir = d;
		switch (d){
		case Direction::UP:
			if (m_pos.x != -1 && m_pos.x < TileManager::getInstance()->getSize() && canMove(d)){
				TileManager::getInstance()->setExitDirection(m_pos, d);
				m_pos.y -= 1;
				m_targetPos.y -= 500 / TileManager::getInstance()->getSize();
				m_moving = true;
				addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
				TileManager::getInstance()->setUsed(m_pos);
				TileManager::getInstance()->setUsedColour(getColour());
				TileManager::getInstance()->setEnterDirection(m_pos, Direction::DOWN);
				PowerUpManager::getInstance()->updatePowerUp(m_pos.x, m_pos.y);
				AchievementManager::getInstance()->incrementSteps();
			}
			break;
		case Direction::LEFT:
			if (m_pos.x != -1 && m_pos.x != 0 && canMove(d)){
				TileManager::getInstance()->setExitDirection(m_pos, d);
				m_pos.x -= 1;
				m_targetPos.x -= 500 / TileManager::getInstance()->getSize();
				m_moving = true;
				addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
				TileManager::getInstance()->setUsed(m_pos);
				TileManager::getInstance()->setUsedColour(getColour());
				TileManager::getInstance()->setEnterDirection(m_pos, Direction::RIGHT);
				PowerUpManager::getInstance()->updatePowerUp(m_pos.x, m_pos.y);
				AchievementManager::getInstance()->incrementSteps();
			}
			break;
		case Direction::DOWN:
			if (m_pos.x != -1 && m_pos.x < TileManager::getInstance()->getSize() && canMove(d)){
				TileManager::getInstance()->setExitDirection(m_pos, d);
				m_pos.y += 1;
				m_targetPos.y += 500 / TileManager::getInstance()->getSize();
				m_moving = true;
				addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
				TileManager::getInstance()->setUsed(m_pos);
				TileManager::getInstance()->setUsedColour(getColour());
				TileManager::getInstance()->setEnterDirection(m_pos, Direction::UP);
				PowerUpManager::getInstance()->updatePowerUp(m_pos.x, m_pos.y);
				AchievementManager::getInstance()->incrementSteps();
			}
			break;
		case Direction::RIGHT:
			if (m_pos.x == TileManager::getInstance()->getSize() - 1 && m_pos.y == TileManager::getInstance()->getSize() / 2){
				if (getColour() == TileManager::getInstance()->getFinishColor()){
					TileManager::getInstance()->setExitDirection(m_pos, d);
					m_pos.x += 1;
					m_targetPos.x += 500 / TileManager::getInstance()->getSize();
					m_moving = true;
					AchievementManager::getInstance()->incrementSteps();
					AchievementManager::getInstance()->setRoomComplete(true);
				}
			}
			else if (m_pos.x == -1 || canMove(d) && m_pos.x < TileManager::getInstance()->getSize()){
				TileManager::getInstance()->setExitDirection(m_pos, d);
				m_pos.x += 1;
				m_targetPos.x += 500 / TileManager::getInstance()->getSize();
				addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
				m_moving = true;
				TileManager::getInstance()->setUsed(m_pos);
				TileManager::getInstance()->setUsedColour(getColour());
				TileManager::getInstance()->setEnterDirection(m_pos, Direction::LEFT);
				PowerUpManager::getInstance()->updatePowerUp(m_pos.x, m_pos.y);
				AchievementManager::getInstance()->incrementSteps();
			}
			break;
		}
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
		if (random == 0 && m_pos.x > 0 && canMove(Direction::LEFT) &&
			TileManager::getInstance()->floodFillCheck(m_pos.x - 1, m_pos.y, finalPos.x, finalPos.y)){
			m_pos.x--;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		// up
		else if (random == 1 && canMove(Direction::UP) &&
			TileManager::getInstance()->floodFillCheck(m_pos.x, m_pos.y - 1, finalPos.x, finalPos.y)){
			m_pos.y--;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		//right
		else if (random == 2 && canMove(Direction::RIGHT) &&
			TileManager::getInstance()->floodFillCheck(m_pos.x + 1, m_pos.y, finalPos.x, finalPos.y)){
			m_pos.x++;
			addColour(TileManager::getInstance()->colourAt(m_pos.x, m_pos.y));
			TileManager::getInstance()->setUsed(m_pos);
		}
		// down
		else if (random == 3 && canMove(Direction::DOWN) &&
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
	// set the player world position
	m_worldPos = sf::Vector2f(m_pos.x * (500 / TileManager::getInstance()->getSize()) + 150,
		m_pos.y * (500 / TileManager::getInstance()->getSize()));
	m_targetPos = m_worldPos;
	m_moving = false;
}



