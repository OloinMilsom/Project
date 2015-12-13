#include "stdafx.h"
#include "TimedGameScene.h"

TimedGameScene::TimedGameScene(){
	m_currSize = 3;
	m_timer = 9;
	TileManager::getInstance()->initialise(m_currSize);

	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();
}

TimedGameScene::~TimedGameScene(){
	delete m_player;
}

void TimedGameScene::update(sf::Event* e, sf::RenderWindow* window){
	sf::Time dt = m_deltaClock.restart();
	m_timer -= dt.asSeconds();

	if (m_timer <= 0){
		SceneManager::getInstance()->goToScene(SceneID::TIMEGAMEOVER);
		m_timer = 10;
		m_currSize = 3;
		TileManager::getInstance()->initialise(m_currSize);
		m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
		m_player->resetColour();
		m_player->addColour(TileManager::getInstance()->getStartColor());
		m_player->goalFinder();
	}

	while (window->pollEvent(*e))
	{
		// Close window : exit 
		if (e->type == sf::Event::Closed)
			window->close();

		if (e->type == sf::Event::KeyPressed) {
			if (e->key.code == sf::Keyboard::Escape){
				window->close();
			}
			if (e->key.code == sf::Keyboard::Num1){
				SoundManager::getInstance()->muteEffects();
			}
			if (e->key.code == sf::Keyboard::Num2){
				SoundManager::getInstance()->muteMusic();
			}
			if (e->key.code == sf::Keyboard::W)
			{
				m_player->move(Direction::UP);
			}
			else if (e->key.code == sf::Keyboard::A)
			{
				m_player->move(Direction::LEFT);
			}
			else if (e->key.code == sf::Keyboard::S)
			{
				m_player->move(Direction::DOWN);
			}
			else if (e->key.code == sf::Keyboard::D)
			{
				m_player->move(Direction::RIGHT);
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
					if (m_currSize < 11)
						m_currSize += 2;
					m_timer += m_currSize * 3;
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

void TimedGameScene::draw(sf::RenderWindow* window){
	TileManager::getInstance()->draw(window);
	window->setTitle(std::to_string(m_timer));
	sf::RectangleShape rect(sf::Vector2f(100, 100));
	rect.setFillColor(m_player->getColour());
	window->draw(rect);
	m_player->draw(window);
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setFillColor(m_player->getColour());
	window->draw(r);
}

void TimedGameScene::start(){
	m_deltaClock.restart();
}

void TimedGameScene::stop(){

}