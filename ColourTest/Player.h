#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include "TileManager.h"
#include "Direction.h"
#include <vector>

class Player{
private:
	sf::Vector2f m_pos;
	//std::vector<sf::Color> m_colours;
	int m_red;
	int m_green;
	int m_blue;
	const int m_colourDevision = 3;
public:
	Player();
	Player(int x, int y);
	sf::Color getColour() const;
	sf::Vector2f getPos() const;
	sf::Vector2f getWorldPos() const;
	void setPos(sf::Vector2f);
	void resetColour();
	void addColour(sf::Color c);
	bool canMove(Direction dir);
	void move(Direction d);
	void goalFinder();
};

#endif // !PLAYER_H
