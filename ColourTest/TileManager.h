#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <vector>

class TileManager {
private:
	static TileManager * m_instance;
	TileManager();
	std::vector<Tile *> m_tiles;
	Tile * m_start;
	Tile * m_finish;
	int m_currentSize;

public:
	~TileManager();
	static TileManager * getInstance();
	void initialise(int size);
	void draw(sf::RenderWindow * window) const;

	Tile * at(int x, int y) const;
	bool checkWallAt(int x, int y, Direction dir) const;
	sf::Color colourAt(int x, int y) const;
	sf::Color getStartColor() const;
	sf::Color getFinishColor() const;
	int getSize() const;

	void setUsed(sf::Vector2f pos);
	void setUsedColour(sf::Color current);
	void setFinalColour(sf::Color current);

	//int checkAdjacent(int x, int y) const;
	bool floodFillCheck(int x, int y, int targetX, int targetY) const;

	void resetUsed();
	void resetChecked();
	void resetRoom();
};

#endif