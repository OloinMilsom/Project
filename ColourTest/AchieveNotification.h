#ifndef ACHIEVENOTIFICATION_H
#define ACHIEVENOTIFICATION_H

#include "stdafx.h"

class AchieveNotification {
public:
	AchieveNotification(std::string achiementName, sf::Font * font);
	void update();
	void draw(sf::RenderWindow * window) const;
	bool getAlive() const;
private:
	int m_lifeTime;
	sf::Text m_text;
	sf::Vector2f m_textPos;
	sf::RectangleShape m_shape;
	sf::Vector2f m_shapePos;
	bool m_alive;
};

#endif