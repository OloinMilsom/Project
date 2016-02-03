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
		m_achievements.insert(std::make_pair(key, value == "1"));
	}
	myfile.close();
}

void AchievementManager::saveToFile(){
	int i = 0;
}

AchievementManager* AchievementManager::getInstance(){
	if (m_instance == nullptr)
	{
		m_instance = new AchievementManager();
	}
	return m_instance;
}

void AchievementManager::update(){
	if (m_roomComplete && m_roomSize == 3 && m_numberOfSteps == 4)
	{
		m_achievements["3x3 Straight Across"] = true;
	}
	if (m_roomComplete && m_roomSize == 5 && m_numberOfSteps == 4)
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

void AchievementManager::setRoomSize(int arg){
	m_roomSize = arg;
}

void AchievementManager::incrementSteps(){
	m_numberOfSteps++;
}

void AchievementManager::setRoomComplete(bool arg){
	m_roomComplete = arg;
}

