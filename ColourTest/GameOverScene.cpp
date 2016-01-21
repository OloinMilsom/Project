#include "GameOverScene.h"
#include "XBoxController.h"

GameOverScene::GameOverScene(sf::Font * font, std::string label, SceneID id) : m_cameFrom(id)
{
	m_buttons.push_back(Button(sf::Vector2f(200, 200), sf::Vector2f(100, 50), "Retry", font));
	m_buttons.push_back(Button(sf::Vector2f(200, 275), sf::Vector2f(100, 50), "Quit", font));
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
}

void GameOverScene::draw(sf::RenderWindow* window){
	window->draw(m_label);
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i].draw(window);
	}
}

void GameOverScene::start(){

}

void GameOverScene::stop(){

}