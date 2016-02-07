#ifndef POWERUPMANAGER_H
#define POWERUPMANAGER_H

#include "stdafx.h"
#include "PowerUp.h"

class PowerUpManager{
public:
	static PowerUpManager * getInstance();

	void draw(sf::RenderWindow * window);

	void addPowerUp(PowerUp powerUp);
	void updatePowerUp(int x, int y);
	bool checkActive(PowerUp::Type type);
	void newRoom();
	void resetRoom();

private:
	PowerUpManager();

	static PowerUpManager* m_instance;

	std::vector<PowerUp> m_powerUps;
};

#endif