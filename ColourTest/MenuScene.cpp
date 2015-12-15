#include "stdafx.h"
#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(sf::Font* font){
	sf::Texture m_backgroundImg;
	m_buttons.push_back(Button(sf::Vector2f(340, 200), sf::Vector2f(100, 50), SceneID::GAME, "PLAY", font));
	m_buttons.push_back(Button(sf::Vector2f(300, 280), sf::Vector2f(180, 50), SceneID::TIMEDGAME, "TIME TRIAL", font));
}

MenuScene::~MenuScene(){

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
			if (e->key.code == sf::Keyboard::Num1){
				SoundManager::getInstance()->muteEffects();
			}
			if (e->key.code == sf::Keyboard::Num2){
				SoundManager::getInstance()->muteMusic();
			}
			if (e->key.code == sf::Keyboard::Num3){
				SoundManager::getInstance()->muteSpatial();
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (int i = 0; i < m_buttons.size(); i++)
			{
				m_buttons[i].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x,
					sf::Mouse::getPosition(*window).y));
			}
		}
		//std::cout << "x: " << sf::Mouse::getPosition().x - window->getView().getViewport().left << "y: " << sf::Mouse::getPosition().y - window->getView().getViewport().top << std::endl;
	}
}

void MenuScene::draw(sf::RenderWindow* window){
	m_backgroundImg.loadFromFile("res/images/Title.jpg");
	sf::Sprite m_sprBackground(m_backgroundImg);
	window->draw(m_sprBackground);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
}

void MenuScene::start(){

}

void MenuScene::stop(){

}