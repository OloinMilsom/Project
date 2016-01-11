#ifndef TILE_H
#define TILE_H

#include "stdafx.h"
#include "Wall.h"

class Tile {
private:
	sf::Color m_col;
	sf::Color m_originalCol;
	sf::Vector2f m_pos;
	std::vector<Wall> m_walls;
	sf::Sprite m_sprite;
	int m_size;
	bool m_used;
	bool m_floodChecked;
public:
	Tile();
	Tile(int x, int y, int size, sf::Color);
	//constructor used to prevent two colours next to eachother
	Tile(int x, int y, int size, sf::Color above, sf::Color left, sf::Sprite);
	void draw(sf::RenderWindow * window) const;
	sf::Color getColour() const;
	bool getUsed() const;
	bool getChecked() const;
	int getWallCount() const;
	sf::Vector2f getPos() const;
	bool checkWall(Direction dir) const;
	void setColour(sf::Color);
	void setUsed(bool);
	void setChecked(bool);
	void addWalls(Direction direction);
	void reset();
};

#endif // !TILE_H
