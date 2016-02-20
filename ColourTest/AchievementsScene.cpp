#include "stdafx.h"
#include "AchievementsScene.h"
#include <iostream>

AchievementsScene::AchievementsScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(400, 380), sf::Vector2f(160, 50), "RETURN", font));

	sf::Texture * backgroundImg = new sf::Texture;
	backgroundImg->loadFromFile("res/images/Title.jpg");

	m_sprBackground = sf::Sprite();
	m_sprBackground.setTexture(*backgroundImg);
	m_sprBackground.setPosition(0, 0);
	m_sprBackground.setTextureRect(sf::IntRect(0, 0, m_sprBackground.getLocalBounds().width, m_sprBackground.getLocalBounds().height));
	m_sprBackground.setScale(800 / m_sprBackground.getLocalBounds().width, 640 / m_sprBackground.getLocalBounds().height);

	std::map<std::string, bool> achievements = AchievementManager::getInstance()->getAchievements();
	int i = 0;
	for (std::map<std::string, bool>::iterator iter = achievements.begin(); iter != achievements.end(); iter++)
	{
		m_achievements.push_back(sf::Text(iter->first + "\t" + (iter->second ? "Unlocked" : "Locked"), *font, 24));
		m_achievements[i].setPosition(20, 10 + (30 * i));
		i++;
	}
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
		}
	}
}

void AchievementsScene::draw(sf::RenderWindow* window){
	window->draw(m_sprBackground);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
	for (int i = 0; i < m_achievements.size(); i++)
	{
		window->draw(m_achievements[i]);
	}
}

void AchievementsScene::start(){
	std::map<std::string, bool> achievements = AchievementManager::getInstance()->getAchievements();
	int i = 0;
	for (std::map<std::string, bool>::iterator iter = achievements.begin(); iter != achievements.end(); iter++)
	{
		m_achievements[i].setString(iter->first + "\t" + (iter->second ? "Unlocked" : "Locked"));
		i++;
	}
}

void AchievementsScene::stop(){
	buttonsStop();
}