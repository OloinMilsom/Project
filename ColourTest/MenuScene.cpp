#include "stdafx.h"
#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(400, 240), sf::Vector2f(220, 50), "PLAY", font));
	m_buttons.push_back(Button(sf::Vector2f(400, 300), sf::Vector2f(220, 50), "TIME TRIAL", font));
	m_buttons.push_back(Button(sf::Vector2f(400, 360), sf::Vector2f(220, 50), "ACHIEVEMENTS", font));
	m_buttons.push_back(Button(sf::Vector2f(400, 420), sf::Vector2f(220, 50), "OPTIONS", font));
	m_buttons.push_back(Button(sf::Vector2f(400, 480), sf::Vector2f(220, 50), "TUTORIAL", font));

	m_backgroundTex = new sf::Texture();
	m_backgroundTex->loadFromFile("res/images/Title.jpg");
	m_titleTex = new sf::Texture();
	m_titleTex->loadFromFile("res/images/name.png");

	m_sprBackground.setTexture(*m_backgroundTex);
	m_sprBackground.setPosition(0, 0);
	m_sprBackground.setTextureRect(sf::IntRect(0, 0, m_sprBackground.getLocalBounds().width, m_sprBackground.getLocalBounds().height));
	m_sprBackground.setScale(800 / m_sprBackground.getLocalBounds().width, 640 / m_sprBackground.getLocalBounds().height);
	
	m_title.setTexture(*m_titleTex);
	m_title.setOrigin(m_title.getLocalBounds().width / 2, m_title.getLocalBounds().height / 2);
	m_title.setPosition(400, 100);
	m_title.setTextureRect(sf::IntRect(0, 0, m_title.getLocalBounds().width, m_title.getLocalBounds().height));
	m_title.setScale(700 / m_title.getLocalBounds().width, 100 / m_title.getLocalBounds().height);
}

MenuScene::~MenuScene(){
	int x = 0;
}

void MenuScene::update(sf::Event* e, sf::RenderWindow* window){
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
				SceneManager::getInstance()->goToScene(SceneID::GAME);
			}
			else if (m_buttons[1].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToScene(SceneID::TIMEDGAME);
			}
			else if(m_buttons[2].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToScene(SceneID::ACHIEVEMENTS);
			}
			else if(m_buttons[3].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToScene(SceneID::OPTIONS);
			}
			else if(m_buttons[4].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
				SceneManager::getInstance()->goToScene(SceneID::TUTORIAL);
			}
		}
		if (e->type == sf::Event::MouseMoved) {
			for (int i = 0; i < m_buttons.size(); i++)
			{
				m_buttons[i].isMouseOver(sf::Vector2f(sf::Mouse::getPosition(*window).x,
					sf::Mouse::getPosition(*window).y));
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
					else if (XBoxController::getStickDirection(0, XBoxController::XBoxStick::Left).y > 0 && i < m_buttons.size() - 1 ) {
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
			if (m_buttons[0].getSelected()){
				SceneManager::getInstance()->goToScene(SceneID::GAME);
			}
			if (m_buttons[1].getSelected()){
				SceneManager::getInstance()->goToScene(SceneID::TIMEDGAME);
			}
			if (m_buttons[2].getSelected()){
				SceneManager::getInstance()->goToScene(SceneID::ACHIEVEMENTS);
			}
			if (m_buttons[3].getSelected()){
				SceneManager::getInstance()->goToScene(SceneID::OPTIONS);
			}
			if (m_buttons[4].getSelected()) {
				SceneManager::getInstance()->goToScene(SceneID::TUTORIAL);
			}
		}
	}
}

void MenuScene::draw(sf::RenderWindow* window){
	window->draw(m_sprBackground);
	window->draw(m_title);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
}

void MenuScene::start(){

}

void MenuScene::stop(){
	buttonsStop();
}