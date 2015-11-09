#include "stdafx.h"
#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene(sf::Font* font){
	m_buttons.push_back(Button(sf::Vector2f(200, 100), sf::Vector2f(100, 50), SceneID::GAME, "Play", font));
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
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			m_buttons[0].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, 
												sf::Mouse::getPosition(*window).y));
		}
		//std::cout << "x: " << sf::Mouse::getPosition().x - window->getView().getViewport().left << "y: " << sf::Mouse::getPosition().y - window->getView().getViewport().top << std::endl;
	}
}

void MenuScene::draw(sf::RenderWindow* window){
	m_buttons[0].draw(window);
}