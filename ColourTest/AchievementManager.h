#ifndef ACHIEVEMENTMANAGER_H
#define ACHIEVEMENTMANAGER_H

#include "stdafx.h"
#include "SceneID.h"
#include "AchieveNotification.h"
#include <map>
#include <fstream>

#include <iostream>

class AchievementManager {
public:
	static AchievementManager * getInstance();
	void saveToFile();
	
	void update();
	void draw(sf::RenderWindow* window) const;
	void roomOver();
	void gameOver();

	std::map<std::string, bool> getAchievements();

	void setRoomSize(int);
	void incrementSteps();
	void setRoomComplete(bool);

	void setFont(sf::Font* font);
	
private:
	AchievementManager();

	std::map<std::string, bool> m_achievements;
	std::vector<AchieveNotification> m_notifications;

	static AchievementManager* m_instance;
	int m_roomSize;
	int m_numberOfSteps;
	bool m_roomComplete;
	SceneID m_currentScene;
	sf::Font * m_font;
};

#endif