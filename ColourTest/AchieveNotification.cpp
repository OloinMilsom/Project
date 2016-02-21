#include "AchieveNotification.h"

AchieveNotification::AchieveNotification(std::string achiementName, sf::Font * font) : m_alive(true), m_lifeTime(240){
	m_text.setCharacterSize(24);
	m_text.setFont(*font);
	m_text.setColor(sf::Color::White);
	m_text.setString(achiementName);
	m_textPos = sf::Vector2f(10, 610);
	m_text.setPosition(m_textPos);

	m_shape.setFillColor(sf::Color(60, 30, 200));
	m_shape.setOutlineColor(sf::Color(20, 10, 66));
	m_shape.setOutlineThickness(3);
	m_shapePos = sf::Vector2f(0, 600);
	m_shape.setPosition(m_shapePos);
	m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width + 20, m_text.getGlobalBounds().height + 20));
}

void AchieveNotification::update(){
	m_lifeTime--;
	if (m_lifeTime > 180) {
		float yChange = m_shape.getSize().y * ((240 - m_lifeTime) / 60.0);

		m_shapePos.y = 600 - yChange;
		m_shape.setPosition(m_shapePos);

		m_textPos.y =  610 - yChange;
		m_text.setPosition(m_textPos);
	}
	else if (m_lifeTime == 180){
		m_shapePos.y = 600 - m_shape.getSize().y;
		m_shape.setPosition(m_shapePos);

		m_textPos.y = 610 - m_shape.getSize().y;
		m_text.setPosition(m_textPos);
	}
	else if (m_lifeTime < 0)
	{
		m_alive = false;
	}
	else if (m_lifeTime <= 60) {
		float yChange = m_shape.getSize().y * ((m_lifeTime) / 60.0);

		m_shapePos.y = 600 - yChange;
		m_shape.setPosition(m_shapePos);

		m_textPos.y = 610 - yChange;
		m_text.setPosition(m_textPos);
	}
}

void AchieveNotification::draw(sf::RenderWindow * window) const{
	window->draw(m_shape);
	window->draw(m_text);
}

bool AchieveNotification::getAlive() const{
	return m_alive;
}