#ifndef BUTTON_H
#define BUTTON_H

#include "stdafx.h"
#include "SceneManager.h"
#include "SceneID.h"

class Button{
private:
	sf::Vector2f m_position;
	sf::Vector2f m_dimensions;
	SceneID m_goTo;
	sf::Text m_title;
public:
	Button(sf::Vector2f pos = sf::Vector2f(0, 0), sf::Vector2f dims = sf::Vector2f(0.0f, 0.0f), 
			SceneID goTo = SceneID::MENU, std::string m_title = "Title",
			sf::Font* font = nullptr);
	void isClicked(sf::Vector2f);
	void draw(sf::RenderWindow* window);
};

#endif
