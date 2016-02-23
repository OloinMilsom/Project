#include "PowerUp.h"
#include "AchievementManager.h"

PowerUp::PowerUp(float size, sf::Vector2f position, sf::Vector2f coords, sf::Vector2f moveTo) : m_pos(position + sf::Vector2f(size, size)), m_tileCoords(coords), m_moveTo(moveTo), m_initialPos(m_pos){
	m_texture = new sf::Texture();
	m_texture->loadFromFile("res/images/powerup.png");
	m_explosionTex = new sf::Texture();
	m_explosionTex->loadFromFile("res/images/sparkle.png");

	m_sprite.setTexture(*m_texture);

	m_sprite.setPosition(m_pos);
	m_sprite.setOrigin(size / 2, size / 2);
	m_sprite.setScale(size / m_sprite.getLocalBounds().width, size / m_sprite.getLocalBounds().height);

	m_type = static_cast<Type>(rand() % 4);
	m_moving = false;
	m_active = false;
	m_visible = true;
}

void PowerUp::draw(sf::RenderWindow * window) const{
	if (m_visible)
		window->draw(m_sprite);
	if (!m_particles.empty()) {
		for (std::vector<std::pair<sf::Sprite, sf::Vector2f>>::const_iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
		{
			window->draw(iter->first);
		}
	}
}

void PowerUp::update(){
	if (m_moving && m_pos.x > m_moveTo.x - 10 && m_pos.x < m_moveTo.x + 10 &&
		m_pos.y > m_moveTo.y - 10 && m_pos.y < m_moveTo.y + 10){
		m_moving = false;
		m_exploding = true;
		m_visible = false;
		makeParticles();
		m_pos = m_moveTo;
		m_sprite.setPosition(m_pos);
	}
	if (m_moving){
		// velocity += acceleration
		m_vel.y += m_yAccel;
		// position += velocity
		m_pos += m_vel;
		m_sprite.setPosition(m_pos);
	}
	if (m_exploding){
		for (std::vector<std::pair<sf::Sprite, sf::Vector2f>>::iterator iter = m_particles.begin(); iter != m_particles.end(); iter++)
		{
			sf::Vector2f pos = iter->first.getPosition();
			pos += iter->second;
			iter->first.setPosition(pos);
			if ((pos.x - m_moveTo.x) * (pos.x - m_moveTo.x) + (pos.y - m_moveTo.y) * (pos.y - m_moveTo.y) > 12500){
				m_particles.erase(iter);
				break;
			}
		}
	}
}

bool PowerUp::isSteppedOn(int x, int y){
	return (m_tileCoords.x == x && m_tileCoords.y == y) && m_visible;
}

PowerUp::Type PowerUp::getType(){
	return m_type;
}

bool PowerUp::getActive(){
	return m_active;
}

void PowerUp::setActive(bool arg){
	m_active = arg;
	if (m_active){
		// PHYSICS: PROJECTILE AND TARGET
		m_moving = true;
		// we want it to take thirty clock ticks to get to the target
		float time = 30;
		// velocity is distance divided by time, in this case we find out x velocity
		m_vel.x = (m_moveTo.x - m_pos.x) / time;
		// distance along y axis we wish to travel
		float yDist = m_moveTo.y - m_pos.y;
		// s = ut + 0.5at^2
		// ut = s - 0.5at^2
		// u = (s - 0.5at^2) / t
		m_vel.y = (yDist - 0.5f * m_yAccel * (time * time)) / time;
		AchievementManager::getInstance()->incrementPowerups();
	}
}

void PowerUp::reset(){
	m_active = false;
	m_moving = false;
	m_exploding = false;
	m_visible = true;
	m_pos = m_initialPos;
	m_sprite.setPosition(m_pos);
	m_particles.clear();
}

void PowerUp::makeParticles(){
	for (int i = 0; i < 20; i++)
	{
		sf::Sprite s(*m_explosionTex);
		s.setPosition(m_moveTo);

		sf::Vector2f v(rand() % 9 - 4, rand() % 9 - 4);
		if (v == sf::Vector2f(0, 0))
			v.x = 1;
		m_particles.push_back(std::make_pair(s, v));
	}
}
