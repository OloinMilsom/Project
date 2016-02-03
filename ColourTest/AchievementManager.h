#ifndef ACHIEVEMENTMANAGER_H
#define ACHIEVEMENTMANAGER_H

#include "stdafx.h"
#include <map>
#include <fstream>

#include <iostream>

class AchievementManager {
public:
	static AchievementManager * getInstance();
	void saveToFile();
	
	void update();
	void roomOver();
	void gameOver();

	void setRoomSize(int);
	void incrementSteps();
	void setRoomComplete(bool);
	
private:
	AchievementManager();

	std::map<std::string, bool> m_achievements;

	static AchievementManager* m_instance;
	int m_roomSize;
	int m_numberOfSteps;
	bool m_roomComplete;
};

#endif