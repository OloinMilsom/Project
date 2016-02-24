#include "stdafx.h"
#include "GameScene.h"
#include <iostream>
#include "PowerUpManager.h"

GameScene::GameScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(800 - 50, 600 - 50), sf::Vector2f(50, 50), "||", font));

	m_currSize = 3;
	m_attempts = m_currSize * m_currSize;
	TileManager::getInstance()->initialise(m_currSize);

	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	m_finishColour = sf::RectangleShape(sf::Vector2f(160, 30));
	m_finishColour.setOrigin(80, 15);
	m_finishColour.setPosition(200, 535);

	m_splitFinish = std::vector<sf::RectangleShape>(3);
	m_splitFinish[0].setFillColor(sf::Color::Red);
	m_splitFinish[1].setFillColor(sf::Color::Green);
	m_splitFinish[2].setFillColor(sf::Color::Blue);

	m_playerColour = sf::RectangleShape(sf::Vector2f(160, 30));
	m_playerColour.setOrigin(80, 15);
	m_playerColour.setPosition(200, 565);

	m_splitPlayer = std::vector<sf::RectangleShape>(3);
	m_splitPlayer[0].setFillColor(sf::Color::Red);
	m_splitPlayer[1].setFillColor(sf::Color::Green);
	m_splitPlayer[2].setFillColor(sf::Color::Blue);

	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("res/images/overlay.png");
	m_overlay.setTexture(*tex);
	m_overlay.setPosition(0, 0);
	m_overlay.setTextureRect(sf::IntRect(0,0,800,500));

	sf::Texture* tex2 = new sf::Texture();
	tex2->loadFromFile("res/images/raindrop.png");
	m_raindropSprite.setTexture(*tex2);

	sf::Texture* tex3 = new sf::Texture();
	tex3->loadFromFile("res/images/ui.png");
	m_ui.setTexture(*tex3);
	m_ui.setPosition(0, 500);
	m_ui.setTextureRect(sf::IntRect(0, 0, 800, 100));

	m_scoreLabel.setCharacterSize(24);
	m_scoreLabel.setFont(*font);
	m_scoreLabel.setColor(sf::Color::White);
	m_scoreLabel.setString("Score: 0");
	m_scoreLabel.setOrigin(m_scoreLabel.getGlobalBounds().width / 2, m_scoreLabel.getGlobalBounds().height / 2);
	m_scoreLabel.setPosition(sf::Vector2f(370, 525));

	m_attemptsLabel.setCharacterSize(24);
	m_attemptsLabel.setFont(*font);
	m_attemptsLabel.setColor(sf::Color::White);
	m_attemptsLabel.setString("Attempts: " + std::to_string(m_attempts));
	m_attemptsLabel.setOrigin(m_attemptsLabel.getGlobalBounds().width / 2, m_attemptsLabel.getGlobalBounds().height / 2);
	m_attemptsLabel.setPosition(sf::Vector2f(370, 555));

	m_playerLabel.setCharacterSize(24);
	m_playerLabel.setFont(*font);
	m_playerLabel.setColor(sf::Color::White);
	m_playerLabel.setString("Player:");
	m_playerLabel.setOrigin(m_playerLabel.getGlobalBounds().width / 2, m_playerLabel.getGlobalBounds().height / 2);
	m_playerLabel.setPosition(sf::Vector2f(60, 555));

	m_finishLabel.setCharacterSize(24);
	m_finishLabel.setFont(*font);
	m_finishLabel.setColor(sf::Color::White);
	m_finishLabel.setString("Finish:");
	m_finishLabel.setOrigin(m_finishLabel.getGlobalBounds().width / 2, m_finishLabel.getGlobalBounds().height / 2);
	m_finishLabel.setPosition(sf::Vector2f(60, 525));

	m_powerUpLabel.setCharacterSize(24);
	m_powerUpLabel.setFont(*font);
	m_powerUpLabel.setColor(sf::Color::White);
	m_powerUpLabel.setString("Powerup: None");
	m_powerUpLabel.setOrigin(m_powerUpLabel.getGlobalBounds().width / 2, m_powerUpLabel.getGlobalBounds().height / 2);
	m_powerUpLabel.setPosition(sf::Vector2f(530, 525));
}

GameScene::~GameScene(){
	delete m_player;
}

void GameScene::update(sf::Event* e, sf::RenderWindow* window){
	m_player->update();
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->updateSpatial(m_player->getWorldPos() + sf::Vector2f(tileSize, tileSize), m_player->getVel());
	PowerUpManager::getInstance()->update();

	if (PowerUpManager::getInstance()->checkActive(PowerUp::Type::FRESH_START)){
		TileManager::getInstance()->resetRoom();
		TileManager::getInstance()->setUsed(m_player->getPos());
		TileManager::getInstance()->setUsedColour(m_player->getColour());
		m_powerUpLabel.setString("Powerup: Fresh Start");
	}
	if (PowerUpManager::getInstance()->checkActive(PowerUp::Type::MORETIME_ATTEMPTS)){
		m_attempts += 3;
		m_attemptsLabel.setString("Attempts: " + std::to_string(m_attempts));
		m_powerUpLabel.setString("Powerup: Attempts");
	}
	if (PowerUpManager::getInstance()->checkActive(PowerUp::Type::SCORE)){
		m_score++;
		m_scoreLabel.setString("Score: " + std::to_string(m_score));
		m_powerUpLabel.setString("Powerup: Score");
	}

	m_raindrops.push_back(RainDrop(m_raindropSprite));

	for (std::vector<RainDrop>::iterator iter = m_raindrops.begin(); iter != m_raindrops.end(); iter++) {
		iter->update();
	}
	for (std::vector<RainDrop>::iterator iter = m_raindrops.begin(); iter != m_raindrops.end(); iter++)
	{
		if (!iter->getAlive()){
			m_raindrops.erase(iter);
			break;
		}
	}

	GameScene::checkWin();

	if (XBoxController::isConnected(0)) {
		GameScene::xboxControls();		
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
	
	sf::Color currPlayer = m_player->getColour();
	m_playerColour.setFillColor(currPlayer);
	int colourWidth = currPlayer.r + currPlayer.g + currPlayer.b;
	if (colourWidth != 0){
		m_splitPlayer[0].setSize(sf::Vector2f(160 * currPlayer.r / colourWidth, 30));
		m_splitPlayer[1].setSize(sf::Vector2f(160 * currPlayer.g / colourWidth, 30));
		m_splitPlayer[2].setSize(sf::Vector2f(160 * currPlayer.b / colourWidth, 30));
	}
	int widthSoFar = 0;
	for (int i = 0; i < 3; i++)
	{
		m_splitPlayer[i].setOrigin(0, 15);
		m_splitPlayer[i].setPosition(120 + widthSoFar, 565);
		widthSoFar += m_splitPlayer[i].getSize().x;
	}
	
	if (PowerUpManager::getInstance()->checkActive(PowerUp::Type::COLOURSPLIT)){
		m_powerUpLabel.setString("Powerup: Colour Split");
		for (int i = 0; i < 3; i++)
		{
			window->draw(m_splitFinish[i]);
			window->draw(m_splitPlayer[i]);
		}
	}
	else {
		window->draw(m_playerColour);
		window->draw(m_finishColour);
	}

	m_player->draw(window);
	
	PowerUpManager::getInstance()->draw(window);

	for (int i = 0; i < m_raindrops.size(); i++)
	{
		m_raindrops[i].draw(window);
	}

	window->draw(m_overlay);
	window->draw(m_ui);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
	window->draw(m_attemptsLabel);
	window->draw(m_scoreLabel);
	window->draw(m_playerLabel);
	window->draw(m_finishLabel);
	window->draw(m_powerUpLabel);
}

void GameScene::start(){
	
	SoundManager::getInstance()->playSpatial(0);
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	
	sf::Color currFinish = TileManager::getInstance()->getFinishColor();
	m_finishColour.setFillColor(currFinish);
	int colourWidth = currFinish.r + currFinish.g + currFinish.b;
	m_splitFinish[0].setSize(sf::Vector2f(160 * currFinish.r / colourWidth, 30));
	m_splitFinish[1].setSize(sf::Vector2f(160 * currFinish.g / colourWidth, 30));
	m_splitFinish[2].setSize(sf::Vector2f(160 * currFinish.b / colourWidth, 30));
	int widthSoFar = 0;
	for (int i = 0; i < 3; i++)
	{
		m_splitFinish[i].setOrigin(0, 15);
		m_splitFinish[i].setPosition(120 + widthSoFar, 535);
		widthSoFar += m_splitFinish[i].getSize().x;
	}
	AchievementManager::getInstance()->setGameMode(SceneID::GAME); 
	AchievementManager::getInstance()->roomOver();
	AchievementManager::getInstance()->setAttempts(m_attempts);
}

void GameScene::stop(){
	m_score = 0;
	m_scoreLabel.setString("Score: " + std::to_string(m_score));
	m_currSize = 3;
	m_attempts = m_currSize * m_currSize;
	m_attemptsLabel.setString("Attempts: " + std::to_string(m_attempts));
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	SoundManager::getInstance()->stopSpatial();

	TileManager::getInstance()->initialise(m_currSize);
	m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	AchievementManager::getInstance()->roomOver();
	PowerUpManager::getInstance()->newRoom();
	buttonsStop();
}

void GameScene::nextRoom(){
	int tileSize = 500 / TileManager::getInstance()->getSize();
		
	m_score++;
	m_scoreLabel.setString("Score: " + std::to_string(m_score));

	// reset powerups
	PowerUpManager::getInstance()->newRoom();

	m_powerUpLabel.setString("Powerup: None");

	// increase the size of the rooms
	if (m_currSize < 11)
		m_currSize += 2;
	TileManager::getInstance()->initialise(m_currSize);

	m_attempts += m_currSize * 0.5f;
	m_attemptsLabel.setString("Attempts: " + std::to_string(m_attempts));

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

	sf::Color currFinish = TileManager::getInstance()->getFinishColor();
	m_finishColour.setFillColor(currFinish);
	int colourWidth = currFinish.r + currFinish.g + currFinish.b;
	m_splitFinish[0].setSize(sf::Vector2f(160 * currFinish.r / colourWidth, 30));
	m_splitFinish[1].setSize(sf::Vector2f(160 * currFinish.g / colourWidth, 30));
	m_splitFinish[2].setSize(sf::Vector2f(160 * currFinish.b / colourWidth, 30));
	int widthSoFar = 0;
	for (int i = 0; i < 3; i++)
	{
		m_splitFinish[i].setOrigin(0, 15);
		m_splitFinish[i].setPosition(120 + widthSoFar, 535);
		widthSoFar += m_splitFinish[i].getSize().x;
	}

	AchievementManager::getInstance()->roomOver();
}

void GameScene::resetRoom() {
	m_attempts--;
	AchievementManager::getInstance()->setAttempts(m_attempts);
	m_attemptsLabel.setString("Attempts: " + std::to_string(m_attempts));
	if (m_attempts <= 0){
		AchievementManager::getInstance()->setCurrScore(m_score);
		SceneManager::getInstance()->goToScene(SceneID::GAMEOVER);
	}
	else{
		// reset powerups
		PowerUpManager::getInstance()->resetRoom();
		TileManager::getInstance()->resetRoom();
		m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
		m_player->resetColour();
	}

	m_powerUpLabel.setString("Powerup: None");
	AchievementManager::getInstance()->roomOver();
}

void GameScene::checkWin(){
	// room complete
	if (m_player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2) && !m_player->getMoving()) {
		GameScene::nextRoom();
	}
	else if (m_player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize() - 1, TileManager::getInstance()->getSize() / 2) && 
			m_player->getColour() == TileManager::getInstance()->getFinishColor()) {
		AchievementManager::getInstance()->setRoomComplete(true);
	}
}

void GameScene::xboxControls(){
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
	if (XBoxController::isButtonPressed(0, XBoxController::XboxButton::B)){
		resetRoom();
	}
	if (XBoxController::isButtonPressed(0, XBoxController::XboxButton::Start)){
		SceneManager::getInstance()->goToPause(SceneID::GAME);
	}
}