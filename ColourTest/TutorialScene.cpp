#include "TutorialScene.h"

TutorialScene::TutorialScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(800 - 50, 600 - 50), sf::Vector2f(50, 50), "||", font));

	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	m_finishColour = sf::RectangleShape(sf::Vector2f(500, 20));
	m_finishColour.setOrigin(250, 10);
	m_finishColour.setPosition(400, 540);

	m_playerColour = sf::RectangleShape(sf::Vector2f(500, 20));
	m_playerColour.setOrigin(250, 10);
	m_playerColour.setPosition(400, 560);

	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("res/images/overlay.png");
	m_overlay.setTexture(*tex);
	m_overlay.setPosition(0, 0);
	m_overlay.setTextureRect(sf::IntRect(0, 0, 800, 500));

	sf::Texture* tex2 = new sf::Texture();
	tex2->loadFromFile("res/images/raindrop.png");
	m_raindropSprite.setTexture(*tex2);

	m_topLabel.setFont(*font);
	m_topLabel.setCharacterSize(24);
	m_topLabel.setColor(sf::Color::White);
	m_bottomLabel.setFont(*font);
	m_bottomLabel.setCharacterSize(24);
	m_bottomLabel.setColor(sf::Color::White);
}

TutorialScene::~TutorialScene(){
	delete m_player;
}

void TutorialScene::update(sf::Event* e, sf::RenderWindow* window){
	m_player->update();
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->updateSpatial(m_player->getWorldPos() + sf::Vector2f(tileSize, tileSize), m_player->getVel());

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

	checkWin();

	if (XBoxController::isConnected(0)) {
		xboxControls();
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
				if (m_currTutorial == 0){
					if (m_player->getPos().x == 0) {
						m_topLabel.setString("Stepping on a tile blends that tile's\ncolour into your colour");
						m_topLabel.setOrigin(m_topLabel.getGlobalBounds().width / 2, m_topLabel.getGlobalBounds().height / 2);

						m_bottomLabel.setString("Your colour is displayed in the path of\nconnected tiles behind you");
						m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
					}
					if (m_player->getPos().x == 1) {
						m_topLabel.setString("Colours combine using and Blend using RGB values");
						m_topLabel.setOrigin(m_topLabel.getGlobalBounds().width / 2, m_topLabel.getGlobalBounds().height / 2);

						m_bottomLabel.setString("");
						m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
					}
					if (m_player->getPos().x == 2) {
						m_topLabel.setString("In order to step on the final tile of a level\nyour colour must be the exact same");
						m_topLabel.setOrigin(m_topLabel.getGlobalBounds().width / 2, m_topLabel.getGlobalBounds().height / 2);

						m_bottomLabel.setString("You can reset a level by pressing R on keyboard\nor B on XBox Controller");
						m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
					}
				}
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

void TutorialScene::draw(sf::RenderWindow* window){
	TileManager::getInstance()->draw(window);

	sf::Color currPlayer = m_player->getColour();
	m_playerColour.setFillColor(currPlayer);
	
	window->draw(m_playerColour);
	window->draw(m_finishColour);

	m_player->draw(window);
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setFillColor(m_player->getColour());
	window->draw(r);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}

	for (int i = 0; i < m_raindrops.size(); i++)
	{
		m_raindrops[i].draw(window);
	}

	window->draw(m_overlay);
	window->draw(m_topLabel);
	window->draw(m_bottomLabel);
}

void TutorialScene::start(){
	int m_currTutorial = 0;
	TileManager::getInstance()->initialiseTutorial(m_currTutorial);
	m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();
	m_player->addColour(TileManager::getInstance()->getStartColor());
	
	m_topLabel.setString("The object of Chromarray is to get\nfrom one side of a room to another.");
	m_topLabel.setOrigin(m_topLabel.getGlobalBounds().width / 2, m_topLabel.getGlobalBounds().height / 2);
	m_topLabel.setPosition(400, 60);

	m_bottomLabel.setString("Press D on Keyboard or Left on DPad or Left Stick");
	m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
	m_bottomLabel.setPosition(400, 400);

	SoundManager::getInstance()->playSpatial(0);
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	sf::Color currFinish = TileManager::getInstance()->getFinishColor();
	m_finishColour.setFillColor(currFinish);
}

void TutorialScene::stop(){
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	SoundManager::getInstance()->stopSpatial();
	m_currTutorial = 0;

	AchievementManager::getInstance()->roomOver();
	buttonsStop();
}

void TutorialScene::nextRoom(){
	SoundManager::getInstance()->playEffect(1);
	if (m_currTutorial < 3) {
		m_currTutorial++;

		m_topLabel.setString("RGB values do not blend in the same way as pigments,\n for example");
		m_topLabel.setOrigin(m_topLabel.getGlobalBounds().width / 2, m_topLabel.getGlobalBounds().height / 2);
		if (m_currTutorial == 1){
			m_bottomLabel.setString("Blue and Red make Magenta");
			m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
		}
		if (m_currTutorial == 2){
			m_bottomLabel.setString("Green and Blue make Cyan");
			m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
		}
		if (m_currTutorial == 3){
			m_bottomLabel.setString("Red and Green make Yellow");
			m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
		}
		TileManager::getInstance()->initialiseTutorial(m_currTutorial);
		m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
		m_player->resetColour();
		m_player->addColour(TileManager::getInstance()->getStartColor());
		// find new tile size
		int tileSize = 500 / TileManager::getInstance()->getSize();

		// update spatial sound effects
		SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
		SoundManager::getInstance()->playEffect(1);
	}
	else {
		SceneManager::getInstance()->goToScene(SceneID::MENU);
	}
}

void TutorialScene::resetRoom() {
	TileManager::getInstance()->resetRoom();
	m_player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();
}

void TutorialScene::checkWin(){
	// room complete
	if (m_player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2) && !m_player->getMoving()) {
		nextRoom();
	}
}

void TutorialScene::xboxControls(){
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