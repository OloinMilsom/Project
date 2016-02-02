#ifndef ACHIEVEMENTMANAGER_H
#define ACHIEVEMENTMANAGER_H

#include "stdafx.h"

class AchievementManager {
public:
	static AchievementManager * getInstance();
private:
	AchievementManager();
	static AchievementManager* m_instance;
};

#endif