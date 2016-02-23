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
	void setTutorialComplete(bool);
	void incrementPowerups();
	void setGameMode(SceneID);
	void setAttempts(int);
	void setTime(float);

	void setFont(sf::Font* font);
	int getHighScore() const;
	int getTimedHighScore() const;
	int getCurrScore() const;
	void setCurrScore(int);
	void setTimedCurrScore(int);
	
private:
	AchievementManager();

	std::map<std::string, bool> m_achievements;
	std::vector<AchieveNotification> m_notifications;
	int m_highScore;
	int m_timedHighScore;
	int m_currScore;

	static AchievementManager* m_instance;
	int m_roomSize;
	int m_numberOfSteps;
	bool m_roomComplete;
	bool m_tutorialComplete;
	int m_noOfPickups;
	int m_currAttempts;
	float m_currTime;

	SceneID m_currentScene;
	sf::Font * m_font;
};

#endif