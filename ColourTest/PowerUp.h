#ifndef POWERUP_H
#define POWERUP_H

#include "stdafx.h"

class PowerUp {
public:
	enum Type {
		COLOURSPLIT,
		NONE
	};
	
	PowerUp(float size = 0.0f, sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f coords = sf::Vector2f(0, 0), sf::Vector2f moveTo = sf::Vector2f(0, 0));
	void draw(sf::RenderWindow * window) const;
	void update();

	bool isSteppedOn(int x, int y);
	Type getType();
	bool getActive();

	void setActive(bool);
	void reset();
private:
	Type m_type;
	sf::Vector2f m_pos;
	sf::Vector2f m_initialPos;
	sf::Vector2f m_vel;
	sf::Vector2f m_moveTo;
	sf::Vector2f m_tileCoords;

	sf::Texture* m_texture;
	sf::Texture* m_explosionTex;
	sf::Sprite m_sprite;

	std::vector<std::pair<sf::Sprite, sf::Vector2f>> m_particles;
	bool m_active;
	bool m_moving;
	bool m_exploding;

	void makeParticles();
};

#endif