#include "AchievementManager.h"

AchievementManager* AchievementManager::m_instance = nullptr;

AchievementManager::AchievementManager(){
	
}

AchievementManager* AchievementManager::getInstance(){
	if (m_instance == nullptr)
	{
		m_instance = new AchievementManager();
	}
	return m_instance;
}