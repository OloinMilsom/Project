#include "stdafx.h"
#include "GameScene.h"
#include <iostream>
#include "XBoxController.h"

GameScene::GameScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(800 - 50, 600 - 50), sf::Vector2f(50, 50), "||", font));

	m_currSize = 3;
	m_attempts = 15;
	TileManager::getInstance()->initialise(m_currSize);

	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	m_finishColour = sf::RectangleShape(sf::Vector2f(500, 20));
	m_finishColour.setOrigin(250, 10);
	m_finishColour.setPosition(400, 540);

	m_playerColour = sf::RectangleShape(sf::Vector2f(500, 20));
	m_playerColour.setOrigin(250, 10);
	m_playerColour.setPosition(400, 560);
}

GameScene::~GameScene(){
	delete m_player;
}

void GameScene::update(sf::Event* e, sf::RenderWindow* window){
	m_player->update();
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->updateSpatial(m_player->getWorldPos() + sf::Vector2f(tileSize, tileSize), m_player->getVel());

	if (XBoxController::isConnected(0)) {
		if (XBoxController::isStickMoving(0, XBoxController::XBoxStick::Left)) {
			sf::Vector2f dir = XBoxController::getStickDirection(0, XBoxController::XBoxStick::Left);
			if (dir.x * dir.x > dir.y * dir.y) {
				if (dir.x > 0) {
					m_player->move(Direction::RIGHT);
				}
				else {
					m_player->move(Direction::LEFT);
				}
			}
			else {
				if (dir.y > 0) {
					m_player->move(Direction::DOWN);
				}
				else {
					m_player->move(Direction::UP);
				}
			}
		}
		if (XBoxController::isDPadPressed(0, Direction::LEFT)){
			m_player->move(Direction::LEFT);
		}
		if (XBoxController::isDPadPressed(0, Direction::UP)){
			m_player->move(Direction::UP);
		}
		if (XBoxController::isDPadPressed(0, Direction::RIGHT)){
			m_player->move(Direction::RIGHT);
		}
		if (XBoxController::isDPadPressed(0, Direction::DOWN)){
			m_player->move(Direction::DOWN);
		}
		if (XBoxController::isButtonPressed(0, XBoxController::XboxButton::A)){
			nextRoom();
		}
		if (XBoxController::isButtonPressed(0, XBoxController::XboxButton::B)){
			resetRoom();
		}
	}

	while (window->pollEvent(*e))
	{
		// Close window : exit 
		if (e->type == sf::Event::Closed)
			window->close();

		if (e->type == sf::Event::JoystickButtonPressed){
			std::cout << e->joystickButton.button;
		}
		if (e->type == sf::Event::JoystickMoved){
			std::cout << sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
		}
		if (e->type == sf::Event::KeyPressed) {
			std::cout << e->key.code;
			if (e->key.code == sf::Keyboard::Escape){
				window->close();
			}
			if (e->key.code == sf::Keyboard::P){
				SoundManager::getInstance()->updateReverb(FMOD_PRESET_SEWERPIPE);
			}
			if (e->key.code == sf::Keyboard::O){
				SoundManager::getInstance()->updateReverb(FMOD_PRESET_PSP_SPACE);
			}
			if (e->key.code == sf::Keyboard::I){
				SoundManager::getInstance()->updateReverb(FMOD_PRESET_UNDERWATER);
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
				resetRoom();
			}
			else if (e->key.code == sf::Keyboard::F)
			{
				nextRoom();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_buttons[0].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToPause(SceneID::GAME);
			}
		}
		if (e->type == sf::Event::MouseMoved) {
			for (int i = 0; i < m_buttons.size(); i++)
			{
				m_buttons[i].isMouseOver(sf::Vector2f(sf::Mouse::getPosition(*window).x,
					sf::Mouse::getPosition(*window).y));
			}
		}
	}
}

void GameScene::draw(sf::RenderWindow* window){
	TileManager::getInstance()->draw(window);
	window->setTitle(std::to_string(m_attempts));
	
	m_playerColour.setFillColor(m_player->getColour());
	window->draw(m_finishColour);
	window->draw(m_playerColour);

	m_player->draw(window);
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setFillColor(m_player->getColour());
	window->draw(r);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
}

void GameScene::start(){
	SoundManager::getInstance()->playSpatial(0);
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	m_finishColour.setFillColor(TileManager::getInstance()->getFinishColor());
}

void GameScene::stop(){
	m_attempts = 15;
	m_currSize = 3;
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	SoundManager::getInstance()->stopSpatial();
	TileManager::getInstance()->initialise(m_currSize);
	m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	AchievementManager::getInstance()->roomOver();
}

void GameScene::nextRoom(){
	int tileSize = 500 / TileManager::getInstance()->getSize();
	// room complete
	if (m_player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2)) {
		// game complete
		if (m_currSize == 11){
			// switch scene
			SceneManager::getInstance()->goToScene(SceneID::GAMEWON);
			SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
			SoundManager::getInstance()->playEffect(1);

		}
		// move to next room
		else {
			// increase the size of the rooms
			m_currSize += 2;
			TileManager::getInstance()->initialise(m_currSize);

			// find new tile size
			tileSize = 500 / TileManager::getInstance()->getSize();

			// update spatial sound effects
			SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
			SoundManager::getInstance()->playEffect(1);

			// find the new path
			m_player->resetColour();
			m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
			m_player->goalFinder();
			m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));

			m_finishColour.setFillColor(TileManager::getInstance()->getFinishColor());
		}
		AchievementManager::getInstance()->roomOver();
	}
}

void GameScene::resetRoom() {
	m_attempts--;
	if (m_attempts < 0){
		SceneManager::getInstance()->goToScene(SceneID::GAMEOVER);
	}
	else{
		TileManager::getInstance()->resetRoom();
		m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
		m_player->resetColour();
	}

	AchievementManager::getInstance()->roomOver();
}