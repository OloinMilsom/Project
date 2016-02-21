#include "stdafx.h"
#include "AchievementsScene.h"
#include <iostream>

AchievementsScene::AchievementsScene(sf::Font* font){
	AchievementManager::getInstance()->setFont(font);
	m_buttons.push_back(Button(sf::Vector2f(400, 550), sf::Vector2f(160, 50), "RETURN", font));
	m_buttons.push_back(Button(sf::Vector2f(200, 550), sf::Vector2f(160, 50), "BACK", font));
	m_buttons.push_back(Button(sf::Vector2f(600, 550), sf::Vector2f(160, 50), "FORWARD", font));

	sf::Texture * backgroundImg = new sf::Texture;
	backgroundImg->loadFromFile("res/images/Title.jpg");

	m_sprBackground = sf::Sprite();
	m_sprBackground.setTexture(*backgroundImg);
	m_sprBackground.setPosition(0, 0);
	m_sprBackground.setTextureRect(sf::IntRect(0, 0, m_sprBackground.getLocalBounds().width, m_sprBackground.getLocalBounds().height));
	m_sprBackground.setScale(800 / m_sprBackground.getLocalBounds().width, 640 / m_sprBackground.getLocalBounds().height);

	std::map<std::string, bool> achievements = AchievementManager::getInstance()->getAchievements();
	int i = 0; 
	std::map<std::string, bool>::iterator iter = achievements.begin();
	std::map<std::string, bool>::iterator endIter = achievements.end();
	for (int i = 0; iter != achievements.end(); iter++, i++)
	{
		sf::Text text(iter->first + "\t" + (iter->second ? "Unlocked" : "Locked"), *font, 24);
		sf::RectangleShape shape(sf::Vector2f(400, 40));

		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);

		text.setPosition(400, 60 * (1 + (i % 8)));
		shape.setPosition(400, 60 * (1 + (i % 8)));
		
		text.setColor(sf::Color::White);
		if (iter->second) {
			shape.setFillColor(sf::Color(60, 30, 200));
			shape.setOutlineColor(sf::Color::White);
			shape.setOutlineThickness(3);
		}
		else {
			shape.setFillColor(sf::Color(20, 10, 66));
		}
		m_achievements.push_back(std::make_pair(shape, text));
	}

	m_currentScreen = 0;
}

AchievementsScene::~AchievementsScene(){

}

void AchievementsScene::update(sf::Event* e, sf::RenderWindow* window){
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
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_buttons[0].isClicked(sf::Vector2f(mousePos.x, mousePos.y))) {
				SceneManager::getInstance()->goToScene(SceneID::MENU);
			}
			if (m_buttons[1].isClicked(sf::Vector2f(mousePos.x, mousePos.y))) {
				if (m_currentScreen > 0)
					m_currentScreen--;
			}
			if (m_buttons[2].isClicked(sf::Vector2f(mousePos.x, mousePos.y))) {
				if (m_currentScreen < ceil(m_achievements.size() / 8))
					m_currentScreen++;
			}
		}
		if (e->type == sf::Event::MouseMoved) {
			for (int i = 0; i < m_buttons.size(); i++)
			{
				m_buttons[i].isMouseOver(sf::Vector2f(mousePos.x, mousePos.y));
			}
		}
		//std::cout << "x: " << sf::Mouse::getPosition().x - window->getView().getViewport().left << "y: " << sf::Mouse::getPosition().y - window->getView().getViewport().top << std::endl;
	}
	if (XBoxController::isConnected(0)) {
		if (XBoxController::isStickMoving(0, XBoxController::XBoxStick::Left)){
			bool anySelected = false;
			for (int i = 0; i < m_buttons.size(); i++)
			{
				if (m_buttons[i].getSelected())
				{
					if (XBoxController::getStickDirection(0, XBoxController::XBoxStick::Left).y < 0 && i > 0) {
						m_buttons[i - 1].setSelected(true);
						m_buttons[i].setSelected(false);
					}
					else if (XBoxController::getStickDirection(0, XBoxController::XBoxStick::Left).y > 0 && i < m_buttons.size() - 1) {
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
		bool down = XBoxController::isDPadPressed(0, Direction::DOWN);
		bool up = XBoxController::isDPadPressed(0, Direction::UP);
		if (up || down){
			bool anySelected = false;
			for (int i = 0; i < m_buttons.size(); i++)
			{
				if (m_buttons[i].getSelected())
				{
					if (up && i > 0) {
						m_buttons[i - 1].setSelected(true);
						m_buttons[i].setSelected(false);
					}
					else if (down && i < m_buttons.size() - 1) {
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
			if (m_buttons[0].getSelected()) {
				SceneManager::getInstance()->goToScene(SceneID::MENU);
			}
			if (m_buttons[1].getSelected()) {
				if (m_currentScreen > 0)
					m_currentScreen--;
			}
			if (m_buttons[2].getSelected()) {
				if (m_currentScreen < ceil(m_achievements.size() / 8))
					m_currentScreen++;
			}
		}
	}
}

void AchievementsScene::draw(sf::RenderWindow* window){
	window->draw(m_sprBackground);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
	for (int i = m_currentScreen * 8; i < m_achievements.size() && i < (m_currentScreen + 1) * 8; i++)
	{
		window->draw(m_achievements[i].first);
		window->draw(m_achievements[i].second);
	}
}

void AchievementsScene::start(){
	std::map<std::string, bool> achievements = AchievementManager::getInstance()->getAchievements();
	int i = 0;
	for (std::map<std::string, bool>::iterator iter = achievements.begin(); iter != achievements.end(); iter++)
	{
		m_achievements[i].second.setString(iter->first + "\t" + (iter->second ? "Unlocked" : "Locked"));
		i++;
	}
}

void AchievementsScene::stop(){
	buttonsStop();
}