#include "GameScene.h"

GameScene::GameScene(){

	TileManager::getInstance()->initialise(5);

	player = new Player(0, TileManager::getInstance()->getSize() / 2);
	player->addColour(TileManager::getInstance()->getStartColor());
	player->goalFinder();
}

GameScene::~GameScene(){
	delete player;
}

void GameScene::update(sf::Event* e){
	if (e->type == sf::Event::KeyPressed) {
		if (e->key.code == sf::Keyboard::W)
		{
			player->move(Player::direction::UP);
		}
		else if (e->key.code == sf::Keyboard::A)
		{
			player->move(Player::direction::LEFT);
		}
		else if (e->key.code == sf::Keyboard::S)
		{
			player->move(Player::direction::DOWN);
		}
		else if (e->key.code == sf::Keyboard::D)
		{
			player->move(Player::direction::RIGHT);
		}
		else if (e->key.code == sf::Keyboard::R)
		{
			TileManager::getInstance()->resetRoom();
			player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
			player->resetColour();
		}
		else if (e->key.code == sf::Keyboard::F)
		{
			if (player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2)){
				player->resetColour();
				TileManager::getInstance()->initialise(TileManager::getInstance()->getSize());
				player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
				player->goalFinder();
				player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
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
	rect.setFillColor(player->getColour());
	window->draw(rect);
	sf::CircleShape circ((500 / TileManager::getInstance()->getSize()) * 0.5f);
	circ.setPosition(sf::Vector2f(player->getPos().x * (500 / TileManager::getInstance()->getSize()) + 150, player->getPos().y * (500 / TileManager::getInstance()->getSize())));
	circ.setFillColor(sf::Color(100,100,100));
	window->draw(circ);
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setFillColor(player->getColour());
	window->draw(r);
	
}