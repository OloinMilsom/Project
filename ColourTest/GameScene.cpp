#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene(){
	m_currSize = 3;
	TileManager::getInstance()->initialise(m_currSize);

	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();
}

GameScene::~GameScene(){
	delete m_player;
}

void GameScene::update(sf::Event* e, sf::RenderWindow* window){
	while (window->pollEvent(*e))
	{
		// Close window : exit 
		if (e->type == sf::Event::Closed)
			window->close();

		if (e->type == sf::Event::KeyPressed) {
			if (e->key.code == sf::Keyboard::Escape){
				window->close();
			}
			if (e->key.code == sf::Keyboard::W)
			{
				m_player->move(Player::direction::UP);
			}
			else if (e->key.code == sf::Keyboard::A)
			{
				m_player->move(Player::direction::LEFT);
			}
			else if (e->key.code == sf::Keyboard::S)
			{
				m_player->move(Player::direction::DOWN);
			}
			else if (e->key.code == sf::Keyboard::D)
			{
				m_player->move(Player::direction::RIGHT);
			}
			else if (e->key.code == sf::Keyboard::R)
			{
				TileManager::getInstance()->resetRoom();
				m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
				m_player->resetColour();
			}
			else if (e->key.code == sf::Keyboard::F)
			{
				if (m_player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2)){
					m_currSize += 2;
					TileManager::getInstance()->initialise(m_currSize);
					m_player->resetColour();
					TileManager::getInstance()->initialise(TileManager::getInstance()->getSize());
					m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
					m_player->goalFinder();
					m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
				}
			}
		}
	}
}

void GameScene::draw(sf::RenderWindow* window){
	for (int y = 0; y < TileManager::getInstance()->getSize(); y++)
	{
		for (int x = 0; x < TileManager::getInstance()->getSize(); x++)
		{
			window->draw(TileManager::getInstance()->getDrawAt(x, y));
		}
	}
	window->draw(TileManager::getInstance()->getStartDraw());
	window->draw(TileManager::getInstance()->getFinishDraw());
	sf::RectangleShape rect(sf::Vector2f(100, 100));
	rect.setFillColor(m_player->getColour());
	window->draw(rect);
	sf::CircleShape circ((500 / TileManager::getInstance()->getSize()) * 0.5f);
	circ.setPosition(sf::Vector2f(m_player->getPos().x * (500 / TileManager::getInstance()->getSize()) + 150, m_player->getPos().y * (500 / TileManager::getInstance()->getSize())));
	circ.setFillColor(sf::Color(100,100,100));
	window->draw(circ);
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setFillColor(m_player->getColour());
	window->draw(r);
	
}