#include "stdafx.h"
#include "OptionsScene.h"
#include <iostream>

OptionsScene::OptionsScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(400, 200), sf::Vector2f(100, 50), "MUSIC", font));
	m_buttons.push_back(Button(sf::Vector2f(400, 260), sf::Vector2f(220, 50), "SOUND EFFECTS", font));
	m_buttons.push_back(Button(sf::Vector2f(400, 380), sf::Vector2f(160, 50), "RETURN", font));

	sf::Texture * backgroundImg = new sf::Texture;
	backgroundImg->loadFromFile("res/images/Title.jpg");

	m_sprBackground = sf::Sprite();
	m_sprBackground.setTexture(*backgroundImg);
	m_sprBackground.setPosition(0, 0);
	m_sprBackground.setTextureRect(sf::IntRect(0, 0, m_sprBackground.getLocalBounds().width, m_sprBackground.getLocalBounds().height));
	m_sprBackground.setScale(800 / m_sprBackground.getLocalBounds().width, 640 / m_sprBackground.getLocalBounds().height);

}

OptionsScene::~OptionsScene(){

}

void OptionsScene::update(sf::Event* e, sf::RenderWindow* window){
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
				SoundManager::getInstance()->muteMusic();
			}
			if (m_buttons[1].isClicked(sf::Vector2f(mousePos.x, mousePos.y))) {
				SoundManager::getInstance()->muteEffects();
			}
			if (m_buttons[2].isClicked(sf::Vector2f(mousePos.x, mousePos.y))) {
				SceneManager::getInstance()->goToScene(SceneID::MENU);
			}
		}
		if (e->type == sf::Event::MouseMoved) {
			for (int i = 0; i < m_buttons.size(); i++)
			{
				m_buttons[i].isMouseOver(sf::Vector2f(mousePos.x, mousePos.y));
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
				SoundManager::getInstance()->muteMusic();
			}
			if (m_buttons[1].getSelected()) {
				SoundManager::getInstance()->muteEffects();
			}
			if (m_buttons[2].getSelected()) {
				SceneManager::getInstance()->goToScene(SceneID::MENU);
			}
		}
	}
}

void OptionsScene::draw(sf::RenderWindow* window){
	window->draw(m_sprBackground);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
}

void OptionsScene::start(){

}

void OptionsScene::stop(){
	buttonsStop();
}