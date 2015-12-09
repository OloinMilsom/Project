#include "TileManager.h"

TileManager * TileManager::m_instance = nullptr;

TileManager::~TileManager(){
	delete m_instance;
	m_instance = nullptr;
	if (!m_tiles.empty()){
		for (int i = 0; i < m_currentSize; i++)
		{
			delete m_tiles[i];
		}
		m_tiles.clear();
	}
	delete m_start;
	delete m_finish;
}

TileManager::TileManager() : m_currentSize(0){
	
}

TileManager * TileManager::getInstance(){
	if (m_instance == nullptr){
		m_instance = new TileManager();
	}
	return m_instance;
}

void TileManager::initialise(int size){
	if (!m_tiles.empty()){
		for (int i = 0; i < m_currentSize; i++)
		{
			delete m_tiles[i];
		}
		m_tiles.clear();
	}
	m_currentSize = size;
	float tileSize = 500 / m_currentSize;
	for (int i = 0; i < m_currentSize * m_currentSize; i++)
	{
		sf::Color above = sf::Color(1, 2, 3);
		sf::Color left = sf::Color(1, 2, 3);
		if (i % m_currentSize > 0)
			left = at(i%m_currentSize - 1, i / m_currentSize)->getColour();
		if (i / m_currentSize > 0)
			above = at(i%m_currentSize, i / m_currentSize - 1)->getColour();
		Tile * newTile = new Tile(150 + (i % m_currentSize) * tileSize, (i / m_currentSize) * tileSize, tileSize, above, left);
		if (i / size != size / 2){
			if (i % size == 0)
				newTile->addWalls(Direction::LEFT);
			if (i / size == 0)
				newTile->addWalls(Direction::UP);
			if (i % size == size - 1)
				newTile->addWalls(Direction::RIGHT);
			if (i / size == size - 1)
				newTile->addWalls(Direction::DOWN);
		}
		m_tiles.push_back(newTile);		
	}
	for (int i = 0; i < m_currentSize * m_currentSize; i++)
	{
		if (!(i / size == size / 2 && (i % size == 0 || i % size == size - 1))){
			int wallCount = at(i % m_currentSize, i / m_currentSize)->getWallCount();
			if (wallCount < 1)
			{
				switch (static_cast<Direction>(rand() % 4)){
				case Direction::UP:
					if (i - size >= 0 && m_tiles[i - size]->getWallCount() < 1){
						m_tiles[i]->addWalls(Direction::UP);
						m_tiles[i - size]->addWalls(Direction::DOWN);
					}
					break;
				case Direction::LEFT:
					if (i - 1 >= 0 && m_tiles[i - 1]->getWallCount() < 1){
						m_tiles[i]->addWalls(Direction::LEFT);
						m_tiles[i - 1]->addWalls(Direction::RIGHT);
					}
					break;
				case Direction::DOWN:
					if (i + size < size * size && m_tiles[i + size]->getWallCount() < 1){
						m_tiles[i]->addWalls(Direction::DOWN);
						m_tiles[i + size]->addWalls(Direction::UP);
					}
					break;
				case Direction::RIGHT:
					if (i + 1 < size * size && m_tiles[i + 1]->getWallCount() < 1){
						m_tiles[i]->addWalls(Direction::RIGHT);
						m_tiles[i + 1]->addWalls(Direction::LEFT);
					}
					break;
				}
			}
		}
	}
	delete m_start;
	delete m_finish;
	m_start = new Tile(150 - tileSize, (m_currentSize / 2) * tileSize, tileSize, sf::Color::Black);
	m_finish = new Tile(150 + m_currentSize * tileSize, (m_currentSize / 2) * tileSize, tileSize, sf::Color::Black);
	m_start->setUsed(true);
}

void TileManager::draw(sf::RenderWindow * window) const{
	for (int i = 0; i < m_tiles.size(); i++)
	{
		m_tiles[i]->draw(window);
	}
	m_start->draw(window);
	m_finish->draw(window);
}

Tile * TileManager::at(int x, int y) const {
	return m_tiles[x + y * m_currentSize];
}

bool TileManager::checkWallAt(int x, int y, Direction dir) const{
	return m_tiles[x + y * m_currentSize]->checkWall(dir);
}

sf::Color TileManager::colourAt(int x, int y) const {
	return m_tiles[x + y * m_currentSize]->getColour();
}

sf::Color TileManager::getStartColor() const {
	return m_start->getColour();
}

sf::Color TileManager::getFinishColor() const {
	return m_finish->getColour();
}

int TileManager::getSize() const{
	return m_currentSize;
}

void TileManager::setUsed(sf::Vector2f pos ){
	m_tiles[pos.x + pos.y * m_currentSize]->setUsed(true);
	//m_tiles[pos.x + pos.y * m_currentSize]->setColour(current);
	
}

void TileManager::setUsedColour(sf::Color current){
	for (int i = 0; i < m_currentSize * m_currentSize; i++)
	{
		if (m_tiles[i]->getUsed()) {
			m_tiles[i]->setColour(current);
		}
	}
	m_start->setColour(current);
}


void TileManager::setFinalColour(sf::Color current){
	m_finish->setColour(current);
}

//int TileManager::checkAdjacent(int x, int y) const{
//	int result = 0;
//	if (x > 0 && !m_tiles[(x-1) + y * m_currentSize]->getUsed()){
//		result++;
//	}
//	if (y > 0 && !m_tiles[x + (y-1) * m_currentSize]->getUsed()){
//		result++;
//	}
//	if (x < m_currentSize-1 && !m_tiles[(x+1) + y * m_currentSize]->getUsed()){
//		result++;
//	}
//	if (y < m_currentSize-1 && !m_tiles[x + (y+1) * m_currentSize]->getUsed()){
//		result++;
//	}
//	return result;
//}

bool TileManager::floodFillCheck(int x, int y, int targetX, int targetY) const{
	m_tiles[x + y * m_currentSize]->setChecked(true);
	if (x == targetX && y == targetY){
		return true;
	}
	if (y > 0 && !m_tiles[x + (y - 1) * m_currentSize]->getUsed() && !m_tiles[x + (y - 1) * m_currentSize]->getChecked()){
		if (floodFillCheck(x, y - 1, targetX, targetY))
			return true;
	}
	if (x > 0 && !m_tiles[(x - 1) + y * m_currentSize]->getUsed() && !m_tiles[(x - 1) + y * m_currentSize]->getChecked()){
		if (floodFillCheck(x - 1, y, targetX, targetY))
			return true;
	}
	if (y < m_currentSize - 1 && !m_tiles[x + (y + 1) * m_currentSize]->getUsed() && !m_tiles[x + (y + 1) * m_currentSize]->getChecked()){
		if (floodFillCheck(x, y + 1, targetX, targetY))
			return true;
	}
	if (x < m_currentSize - 1 && !m_tiles[(x + 1) + y * m_currentSize]->getUsed() && !m_tiles[(x + 1) + y * m_currentSize]->getChecked()){
		if (floodFillCheck(x + 1, y, targetX, targetY))
			return true;
	}
	return false;
}

void TileManager::resetUsed(){
	for (int i = 0; i < m_currentSize * m_currentSize; i++)
	{
		if (m_tiles[i]->getUsed()) {
			m_tiles[i]->setUsed(false);
		}
	}
}

void TileManager::resetChecked(){
	for (int i = 0; i < m_currentSize * m_currentSize; i++)
	{
		if (m_tiles[i]->getChecked()) {
			m_tiles[i]->setChecked(false);
		}
	}
}

void TileManager::resetRoom(){
	for (int i = 0; i < m_currentSize * m_currentSize; i++)
	{
		if (m_tiles[i]->getUsed()) {
			m_tiles[i]->reset();
		}
	}
	m_start->setColour(sf::Color::Black);
}