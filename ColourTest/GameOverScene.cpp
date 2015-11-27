#include "GameOverScene.h"

GameOverScene::GameOverScene(sf::Font * font, std::string label, SceneID id){
	m_buttons.push_back(Button(sf::Vector2f(200, 200), sf::Vector2f(100, 50), id, "Retry?", font));
	m_label.setFont(*font);
	m_label.setString(label);
	m_label.setCharacterSize(24);
	m_label.setColor(sf::Color::White);
	m_label.setStyle(sf::Text::Bold);
	m_label.setPosition(sf::Vector2f(200,100));
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
			m_buttons[0].isClicked(sf::Vector2f(sf::Mouse::getPosition(*window).x,
				sf::Mouse::getPosition(*window).y));
		}
	}
}

void GameOverScene::draw(sf::RenderWindow* window){
	window->draw(m_label);
	m_buttons[0].draw(window);
}

void GameOverScene::start(){

}

void GameOverScene::stop(){

}