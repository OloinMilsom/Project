#ifndef TILEMANAGER_H
#define TILEMANAGER_H

#include "Tile.h"
#include <vector>
#include "AchievementManager.h"
#include "PowerUp.h"

class TileManager {
private:
	static TileManager * m_instance;
	TileManager();
	std::vector<Tile *> m_tiles;
	Tile * m_start;
	Tile * m_finish;
	int m_currentSize;
	sf::Texture m_tex;
	std::vector<sf::Sprite> m_edgeSprites;
	bool m_tutorial;
	
public:
	~TileManager();
	static TileManager * getInstance();
	void initialise(int size);
	void initialiseTutorial(int no);
	void draw(sf::RenderWindow * window) const;

	Tile * at(int x, int y) const;
	bool checkWallAt(int x, int y, Direction dir) const;
	sf::Color colourAt(int x, int y) const;
	sf::Color getStartColor() const;
	sf::Color getFinishColor() const;
	int getSize() const;
	sf::Vector2f getFinishPos() const;

	void setUsed(sf::Vector2f pos);
	void setUsedColour(sf::Color current);
	void setEnterDirection(sf::Vector2f pos, Direction dir);
	void setExitDirection(sf::Vector2f pos, Direction dir);
	void setFinalColour(sf::Color current);
	void setStartDirection();
	void setFinalDirection();

	//int checkAdjacent(int x, int y) const;
	bool floodFillCheck(int x, int y, int targetX, int targetY) const;

	void resetUsed();
	void resetChecked();
	void resetRoom();
};

#endif