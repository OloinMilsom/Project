#include "TutorialScene.h"

TutorialScene::TutorialScene(sf::Font* font){
	m_player = new Player(0, TileManager::getInstance()->getSize() / 2);
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	m_finishColour = sf::RectangleShape(sf::Vector2f(160, 30));
	m_finishColour.setOrigin(80, 15);
	m_finishColour.setPosition(200, 535);

	m_playerColour = sf::RectangleShape(sf::Vector2f(160, 30));
	m_playerColour.setOrigin(80, 15);
	m_playerColour.setPosition(200, 565);

	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile("res/images/overlay.png");
	m_overlay.setTexture(*tex);
	m_overlay.setPosition(0, 0);
	m_overlay.setTextureRect(sf::IntRect(0, 0, 800, 500));

	sf::Texture* tex2 = new sf::Texture();
	tex2->loadFromFile("res/images/raindrop.png");
	m_raindropSprite.setTexture(*tex2);

	sf::Texture* tex3 = new sf::Texture();
	tex3->loadFromFile("res/images/ui.png");
	m_ui.setTexture(*tex3);
	m_ui.setPosition(0, 500);
	m_ui.setTextureRect(sf::IntRect(0, 0, 800, 100));

	m_topLabel.setFont(*font);
	m_topLabel.setCharacterSize(24);
	m_topLabel.setColor(sf::Color::White);
	m_bottomLabel.setFont(*font);
	m_bottomLabel.setCharacterSize(24);
	m_bottomLabel.setColor(sf::Color::White);

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
		if (e->type == sf::Event::Closed){
			window->close();
		}
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
				if (m_currTutorial == 0){
					if (m_player->getPos().x == 0) {
						m_topLabel.setString("Stepping on a tile blends that tile's\ncolour into your colour");
						m_topLabel.setOrigin(m_topLabel.getGlobalBounds().width / 2, m_topLabel.getGlobalBounds().height / 2);

						m_bottomLabel.setString("Your colour is displayed in the path of\nconnected tiles behind you");
						m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
					}
					if (m_player->getPos().x == 1) {
						m_topLabel.setString("Colours combine and blend using RGB values");
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
	}
}

void TutorialScene::draw(sf::RenderWindow* window){
	TileManager::getInstance()->draw(window);

	sf::Color currPlayer = m_player->getColour();
	m_playerColour.setFillColor(currPlayer);
	
	window->draw(m_playerColour);
	window->draw(m_finishColour);

	m_player->draw(window);

	
	for (int i = 0; i < m_raindrops.size(); i++)
	{
		m_raindrops[i].draw(window);
	}

	window->draw(m_overlay);
	window->draw(m_ui);
	window->draw(m_topLabel);
	window->draw(m_bottomLabel);

	window->draw(m_playerLabel);
	window->draw(m_finishLabel);
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

	m_bottomLabel.setString("Use WASD on Keyboard or DPad or Left\nStick on XBox Controller");
	m_bottomLabel.setOrigin(m_bottomLabel.getGlobalBounds().width / 2, m_bottomLabel.getGlobalBounds().height / 2);
	m_bottomLabel.setPosition(400, 400);

	SoundManager::getInstance()->playSpatial(0);
	int tileSize = 500 / TileManager::getInstance()->getSize();
	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	sf::Color currFinish = TileManager::getInstance()->getFinishColor();
	m_finishColour.setFillColor(currFinish);

	AchievementManager::getInstance()->setGameMode(SceneID::TUTORIAL);
}

void TutorialScene::stop(){
	int tileSize = 500 / TileManager::getInstance()->getSize();

	TileManager::getInstance()->initialise(3);
	m_player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
	m_player->resetColour();
	m_player->addColour(TileManager::getInstance()->getStartColor());
	m_player->goalFinder();

	SoundManager::getInstance()->initSpatial(TileManager::getInstance()->getFinishPos() + sf::Vector2f(tileSize, tileSize));
	SoundManager::getInstance()->stopSpatial();
	m_currTutorial = 0;
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
		AchievementManager::getInstance()->setTutorialComplete(true);
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