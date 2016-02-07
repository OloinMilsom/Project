#include "PowerUpManager.h"

PowerUpManager * PowerUpManager::m_instance = nullptr;

PowerUpManager::PowerUpManager(){

}

PowerUpManager* PowerUpManager::getInstance(){
	if (m_instance == nullptr)
	{
		m_instance = new PowerUpManager();
	}
	return m_instance;
}

void PowerUpManager::draw(sf::RenderWindow * window){
	for (std::vector<PowerUp>::iterator iter = m_powerUps.begin(); iter != m_powerUps.end(); iter++)
	{
		iter->draw(window);
	}
}

void PowerUpManager::addPowerUp(PowerUp powerUp){
	m_powerUps.push_back(powerUp);
}

void PowerUpManager::updatePowerUp(int x, int y){
	for (std::vector<PowerUp>::iterator iter = m_powerUps.begin(); iter != m_powerUps.end(); iter++)
	{
		if (iter->isSteppedOn(x, y)){
			iter->setActive(true);
			break;
		}
	}
}

bool PowerUpManager::checkActive(PowerUp::Type type){
	for (std::vector<PowerUp>::iterator iter = m_powerUps.begin(); iter != m_powerUps.end(); iter++)
	{
		if (iter->getActive()) {
			if (iter->getType() == type){
				return true;
			}
		}
	}
	return false;
}

void PowerUpManager::newRoom(){
	m_powerUps.clear();
}

void PowerUpManager::resetRoom(){
	for (std::vector<PowerUp>::iterator iter = m_powerUps.begin(); iter != m_powerUps.end(); iter++)
	{
		iter->setActive(false);
	}
}