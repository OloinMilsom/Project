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
	Tile * at(int x, int y);
	sf::Color colourAt(int x, int y);
	sf::RectangleShape getDrawAt(int x, int y);
	sf::Color getStartColor();
	sf::Color getFinishColor();
	sf::RectangleShape getStartDraw();
	sf::RectangleShape getFinishDraw();
	int getSize();
	void setUsed(sf::Vector2f pos);
	void setUsedColour(sf::Color current);
	void setFinalColour(sf::Color current);
	int checkAdjacent(int x, int y);
	bool floodFillCheck(int x, int y, int targetX, int targetY);
	void resetUsed();
	void resetChecked();
	void resetRoom();
};

#endif