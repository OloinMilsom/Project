#include "stdafx.h"
#include "TimedGameScene.h"
#include "PowerUpManager.h"

TimedGameScene::TimedGameScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(800 - 50, 600 - 50), sf::Vector2f(50, 50), "||", font));

	m_currSize = 3;
	m_timer = 9;
	TileManager::getInstance()->initialise(m_currSize);

	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	m_finishColour = sf::RectangleShape(sf::Vector2f(500, 20));
	m_finishColour.setOrigin(250, 10);
	m_finishColour.setPosition(400, 540);

	m_splitFinish = std::vector<sf::RectangleShape>(3);
	m_splitFinish[0].setFillColor(sf::Color::Red);
	m_splitFinish[1].setFillColor(sf::Color::Green);
	m_splitFinish[2].setFillColor(sf::Color::Blue);

	m_playerColour = sf::RectangleShape(sf::Vector2f(500, 20));
	m_playerColour.setOrigin(250, 10);
	m_playerColour.setPosition(400, 560);

	m_splitPlayer = std::vector<sf::RectangleShape>(3);
	m_splitPlayer[0].setFillColor(sf::Color::Red);
	m_splitPlayer[1].setFillColor(sf::Color::Green);
	m_splitPlayer[2].setFillColor(sf::Color::Blue);
}

TimedGameScene::~TimedGameScene(){
	delete m_player;
}

void TimedGameScene::update(sf::Event* e, sf::RenderWindow* window){
	m_player->update();
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->updateSpatial(m_player->getWorldPos() + sf::Vector2f(tileSize, tileSize), m_player->getVel());

	sf::Time dt = m_deltaClock.restart();
	m_timer -= dt.asSeconds();

	if (m_timer <= 0){
		SceneManager::getInstance()->goToScene(SceneID::TIMEGAMEOVER);		
	}
	TimedGameScene::checkWin();
	//xbox controls
	if (XBoxController::isConnected(0)) {
		TimedGameScene::xboxControls();
	}
	//keyboard controls
	TimedGameScene::keyboardControls(e, window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_buttons[0].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
			SceneManager::getInstance()->goToPause(SceneID::TIMEDGAME);
			m_buttons[0].setSelected(false);
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

void TimedGameScene::draw(sf::RenderWindow* window){

	sf::Color currPlayer = m_player->getColour();
	m_playerColour.setFillColor(currPlayer);
	int colourWidth = currPlayer.r + currPlayer.g + currPlayer.b;
	if (colourWidth != 0){
		m_splitPlayer[0].setSize(sf::Vector2f(500 * currPlayer.r / colourWidth, 20));
		m_splitPlayer[1].setSize(sf::Vector2f(500 * currPlayer.g / colourWidth, 20));
		m_splitPlayer[2].setSize(sf::Vector2f(500 * currPlayer.b / colourWidth, 20));
	}
	int widthSoFar = 0;
	for (int i = 0; i < 3; i++)
	{
		m_splitPlayer[i].setOrigin(0, 10);
		m_splitPlayer[i].setPosition(150 + widthSoFar, 560);
		widthSoFar += m_splitPlayer[i].getSize().x;
	}
	if (PowerUpManager::getInstance()->checkActive(PowerUp::Type::COLOURSPLIT)){
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

	TileManager::getInstance()->draw(window);
	window->setTitle(std::to_string(m_timer));
	sf::RectangleShape rect(sf::Vector2f(100, 100));
	rect.setFillColor(m_player->getColour());
	window->draw(rect);
	m_player->draw(window);
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setFillColor(m_player->getColour());
	window->draw(r);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}

	PowerUpManager::getInstance()->draw(window);
}

void TimedGameScene::start(){
	m_deltaClock.restart();
	SoundManager::getInstance()->playSpatial(0);
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));

	sf::Color currFinish = TileManager::getInstance()->getFinishColor();
	m_finishColour.setFillColor(currFinish);
	int colourWidth = currFinish.r + currFinish.g + currFinish.b;
	m_splitFinish[0].setSize(sf::Vector2f(500 * currFinish.r / colourWidth, 20));
	m_splitFinish[1].setSize(sf::Vector2f(500 * currFinish.g / colourWidth, 20));
	m_splitFinish[2].setSize(sf::Vector2f(500 * currFinish.b / colourWidth, 20));
	int widthSoFar = 0;
	for (int i = 0; i < 3; i++)
	{
		m_splitFinish[i].setOrigin(0, 10);
		m_splitFinish[i].setPosition(150 + widthSoFar, 540);
		widthSoFar += m_splitFinish[i].getSize().x;
	}
}

void TimedGameScene::stop(){
	SoundManager::getInstance()->stopSpatial();
	m_timer = 10;
	m_currSize = 3;
	TileManager::getInstance()->initialise(m_currSize);
	m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();
	buttonsStop();

	PowerUpManager::getInstance()->newRoom();
}

void TimedGameScene::nextRoom(){
	// reset powerups
	PowerUpManager::getInstance()->newRoom();

	int tileSize = 500 / TileManager::getInstance()->getSize();

	// increase the size of the rooms
	if (m_currSize < 11)
		m_currSize += 2;
	TileManager::getInstance()->initialise(m_currSize);

	// reinitialise timer
	m_timer += m_currSize * 3;

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

	AchievementManager::getInstance()->roomOver();
}

void TimedGameScene::resetRoom(){
	TileManager::getInstance()->resetRoom();
	m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();

	AchievementManager::getInstance()->roomOver();
}

void TimedGameScene::checkWin(){
	// room complete
	if (m_player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2)) {
		TimedGameScene::nextRoom();
	}
}

void TimedGameScene::xboxControls(){
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
}

void TimedGameScene::keyboardControls(sf::Event* e, sf::RenderWindow* window){

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
	}
}