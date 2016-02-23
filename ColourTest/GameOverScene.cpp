#include "GameOverScene.h"

GameOverScene::GameOverScene(sf::Font * font, std::string label, SceneID id) : m_cameFrom(id)
{
	m_buttons.push_back(Button(sf::Vector2f(300, 400), sf::Vector2f(100, 50), "Retry", font));
	m_buttons.push_back(Button(sf::Vector2f(500, 400), sf::Vector2f(100, 50), "Quit", font));

	m_backgroundTex = new sf::Texture();
	m_backgroundTex->loadFromFile("res/images/Title.jpg");

	m_sprBackground.setTexture(*m_backgroundTex);
	m_sprBackground.setPosition(0, 0);
	m_sprBackground.setTextureRect(sf::IntRect(0, 0, m_sprBackground.getLocalBounds().width, m_sprBackground.getLocalBounds().height));
	m_sprBackground.setScale(800 / m_sprBackground.getLocalBounds().width, 640 / m_sprBackground.getLocalBounds().height);

	m_label.setFont(*font);
	m_label.setString(label);
	m_label.setCharacterSize(24);
	m_label.setOrigin(m_label.getGlobalBounds().width / 2, m_label.getGlobalBounds().height / 2);
	m_label.setColor(sf::Color::White);
	m_label.setPosition(sf::Vector2f(400,100));

	m_ScoreLabel.setFont(*font);
	if (m_cameFrom == SceneID::GAME)
		m_ScoreLabel.setString("Your Score: " + std::to_string(AchievementManager::getInstance()->getCurrScore()) +
		"\nHighscore: " + std::to_string(AchievementManager::getInstance()->getHighScore()));
	else
		m_ScoreLabel.setString("Your Score: " + std::to_string(AchievementManager::getInstance()->getCurrScore()) +
		"\nHighscore: " + std::to_string(AchievementManager::getInstance()->getTimedHighScore()));
	m_ScoreLabel.setCharacterSize(24);
	m_ScoreLabel.setOrigin(m_ScoreLabel.getGlobalBounds().width / 2, m_ScoreLabel.getGlobalBounds().height / 2);
	m_ScoreLabel.setColor(sf::Color::White);
	m_ScoreLabel.setStyle(sf::Text::Bold);
	m_ScoreLabel.setPosition(sf::Vector2f(400, 200));
}

GameOverScene::~GameOverScene(){

}

void GameOverScene::update(sf::Event* e, sf::RenderWindow* window){
	while (window->pollEvent(*e))
	{
		// Close window : exit 
		if (e->type == sf::Event::Closed)
			window->close();

		if (e->type == sf::Event::KeyPressed) {
			if (e->key.code == sf::Keyboard::Escape){
				window->close();
			}			
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_buttons[0].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToScene(m_cameFrom);
			}
			if (m_buttons[1].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToScene(SceneID::MENU);
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
	if (XBoxController::isConnected(0)) {
		if (XBoxController::isStickMoving(0, XBoxController::XBoxStick::Left)){
			bool anySelected = false;
			for (int i = 0; i < m_buttons.size(); i++)
			{
				if (m_buttons[i].getSelected())
				{
					if (XBoxController::getStickDirection(0, XBoxController::XBoxStick::Left).x < 0 && i > 0) {
						m_buttons[i - 1].setSelected(true);
						m_buttons[i].setSelected(false);
					}
					else if (XBoxController::getStickDirection(0, XBoxController::XBoxStick::Left).x > 0 && i < m_buttons.size() - 1) {
						m_buttons[i + 1].setSelected(true);
						m_buttons[i].setSelected(false);
					}
					anySelected = true;
					break;
				}
			}
			if (!anySelected) {
				m_buttons[0].setSelected(true);
			}
		}
		bool right = XBoxController::isDPadPressed(0, Direction::RIGHT);
		bool left = XBoxController::isDPadPressed(0, Direction::LEFT);
		if (right || left){
			bool anySelected = false;
			for (int i = 0; i < m_buttons.size(); i++)
			{
				if (m_buttons[i].getSelected())
				{
					if (left && i > 0) {
						m_buttons[i - 1].setSelected(true);
						m_buttons[i].setSelected(false);
					}
					else if (right && i < m_buttons.size() - 1) {
						m_buttons[i + 1].setSelected(true);
						m_buttons[i].setSelected(false);
					}
					anySelected = true;
					break;
				}
			}
			if (!anySelected) {
				m_buttons[0].setSelected(true);
			}
		}
		if (XBoxController::isButtonPressed(0, XBoxController::XboxButton::A)) {
			if (m_buttons[0].getSelected()){
				SceneManager::getInstance()->goToScene(m_cameFrom);
			}
			if (m_buttons[1].getSelected()){
				SceneManager::getInstance()->goToScene(SceneID::MENU);
			}
		}
	}
}

void GameOverScene::draw(sf::RenderWindow* window){
	window->draw(m_sprBackground);
	window->draw(m_label);
	sf::RectangleShape s(sf::Vector2f(240, 120));
	s.setFillColor(sf::Color(128, 128, 128));
	s.setPosition(m_ScoreLabel.getPosition());
	s.setOrigin(120,60);
	window->draw(s);
	window->draw(m_ScoreLabel);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
}

void GameOverScene::start(){
	if (m_cameFrom == SceneID::GAME)
		m_ScoreLabel.setString("Your Score: " + std::to_string(AchievementManager::getInstance()->getCurrScore()) +
		"\nHighscore: " + std::to_string(AchievementManager::getInstance()->getHighScore()));
	else
		m_ScoreLabel.setString("Your Score: " + std::to_string(AchievementManager::getInstance()->getCurrScore()) +
		"\nHighscore: " + std::to_string(AchievementManager::getInstance()->getTimedHighScore()));
}

void GameOverScene::stop(){
	buttonsStop();
}