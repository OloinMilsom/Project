#include "AchievementManager.h"

AchievementManager* AchievementManager::m_instance = nullptr;

AchievementManager::AchievementManager(){
	std::ifstream myfile;
	myfile.open("res/achievements.txt");

	std::string key = "";
	std::string value = "";
	while (myfile.good()){
		std::getline(myfile, key, ',');
		std::getline(myfile, value, '\n');
		if (key != "")
			m_achievements.insert(std::make_pair(key, value == "1"));
	}
	myfile.close();
}

void AchievementManager::saveToFile(){
	std::ofstream myfile;
	myfile.open("res/achievements.txt");

	std::string line;
	for (std::map<std::string,bool>::iterator iter = m_achievements.begin(); iter != m_achievements.end(); iter++)
	{
		line = iter->first + "," + (iter->second ? "1" : "0") + "\n";
		myfile << line;
	}
	myfile.close();
}

AchievementManager* AchievementManager::getInstance(){
	if (m_instance == nullptr)
	{
		m_instance = new AchievementManager();
	}
	return m_instance;
}

void AchievementManager::update(){
	if (!m_achievements["3x3 Straight Across"] && m_roomComplete && m_roomSize == 3 && m_numberOfSteps == 3)
	{
		m_achievements["3x3 Straight Across"] = true;
	}
	if (!m_achievements["5x5 Straight Across"] && m_roomComplete && m_roomSize == 5 && m_numberOfSteps == 5)
	{
		m_achievements["5x5 Straight Across"] = true;
	}
}

void AchievementManager::roomOver(){
	m_roomComplete = false;
	m_numberOfSteps = 0;
}

void AchievementManager::gameOver(){
	m_roomSize = 3;
}

std::map<std::string, bool> AchievementManager::getAchievements(){
	return m_achievements;
}

void AchievementManager::setRoomSize(int arg){
	m_roomSize = arg;
}

void AchievementManager::incrementSteps(){
	m_numberOfSteps++;
}

void AchievementManager::setRoomComplete(bool arg){
	m_roomComplete = arg;
}

