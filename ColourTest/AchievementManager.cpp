#include "AchievementManager.h"

AchievementManager* AchievementManager::m_instance = nullptr;

AchievementManager::AchievementManager(){
	std::ifstream myfile;
	myfile.open("res/achievements.txt");

	std::string score;
	std::getline(myfile, score, '\n');
	m_highScore = std::stoi(score);

	std::getline(myfile, score, '\n');
	m_timedHighScore = std::stoi(score);

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
	line = std::to_string(m_highScore) + "\n";
	myfile << line;
	line = std::to_string(m_timedHighScore) + "\n";
	myfile << line;
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
	if (m_currentScene != SceneID::TUTORIAL){
		if (!m_achievements["3x3 Straight Across"] && m_roomComplete && m_roomSize == 3 && m_numberOfSteps == 3)
		{
			m_achievements["3x3 Straight Across"] = true;
			m_notifications.push_back(AchieveNotification("3x3 Straight Across Unlocked", m_font));
		}
		if (!m_achievements["5x5 Straight Across"] && m_roomComplete && m_roomSize == 5 && m_numberOfSteps == 5)
		{
			m_achievements["5x5 Straight Across"] = true;
			m_notifications.push_back(AchieveNotification("5x5 Straight Across Unlocked", m_font));
		}
		if (!m_achievements["7x7 Straight Across"] && m_roomComplete && m_roomSize == 7 && m_numberOfSteps == 7)
		{
			m_achievements["7x7 Straight Across"] = true;
			m_notifications.push_back(AchieveNotification("7x7 Straight Across Unlocked", m_font));
		}
		if (!m_achievements["9x9 Straight Across"] && m_roomComplete && m_roomSize == 9 && m_numberOfSteps == 9)
		{
			m_achievements["9x9 Straight Across"] = true;
			m_notifications.push_back(AchieveNotification("9x9 Straight Across Unlocked", m_font));
		}
		if (!m_achievements["11x11 Straight Across"] && m_roomComplete && m_roomSize == 11 && m_numberOfSteps == 11)
		{
			m_achievements["11x11 Straight Across"] = true;
			m_notifications.push_back(AchieveNotification("11x11 Straight Across Unlocked", m_font));
		}
		if (!m_achievements["Hard Mode"] && m_roomSize > 5 && m_noOfPickups == 0 && m_roomComplete)
		{
			m_achievements["Hard Mode"] = true;
			m_notifications.push_back(AchieveNotification("Hard Mode Unlocked", m_font));
		}
		if (!m_achievements["Long Way Round"] && m_roomSize > 3 && m_numberOfSteps > (m_roomSize * m_roomSize) / 2 && m_roomComplete)
		{
			m_achievements["Long Way Round"] = true;
			m_notifications.push_back(AchieveNotification("Long Way Round Unlocked", m_font));
		}
		if (!m_achievements["Nick of Time"] && m_currentScene == SceneID::TIMEDGAME && m_currTime <= 1 && m_roomComplete)
		{
			m_achievements["Nick of Time"] = true;
			m_notifications.push_back(AchieveNotification("Nick of Time Unlocked", m_font));
		}
		if (!m_achievements["On the Edge"] && m_currentScene == SceneID::GAME && m_currAttempts == 1 && m_roomComplete)
		{
			m_achievements["On the Edge"] = true;
			m_notifications.push_back(AchieveNotification("On the Edge Unlocked", m_font));
		}
		if (!m_achievements["Overpowered"] && m_roomSize > 5 && m_noOfPickups >= 4 && m_roomComplete)
		{
			m_achievements["Overpowered"] = true;
			m_notifications.push_back(AchieveNotification("Overpowered Unlocked", m_font));
		}
		if (!m_achievements["Time to Spare"] && m_currTime > 100)
		{
			m_achievements["Time to Spare"] = true;
			m_notifications.push_back(AchieveNotification("Time to Spare Unlocked", m_font));
		}
		if (!m_achievements["To Easy"] && m_currAttempts > 25)
		{
			m_achievements["To Easy"] = true;
			m_notifications.push_back(AchieveNotification("To Easy Unlocked", m_font));
		}
	}
	if (!m_achievements["Baby Steps"] && m_tutorialComplete)
	{
		m_achievements["Baby Steps"] = true;
		m_notifications.push_back(AchieveNotification("Baby Steps Unlocked", m_font));
	}

	if (!m_notifications.empty()) {
		for (std::vector<AchieveNotification>::iterator iter = m_notifications.begin(); iter != m_notifications.end(); iter++)
		{
			iter->update();
			if (!iter->getAlive())
			{
				m_notifications.erase(iter);
				break;
			}
		}
	}
}

void AchievementManager::draw(sf::RenderWindow* window) const{
	if (!m_notifications.empty()) {
		for (std::vector<AchieveNotification>::const_iterator iter = m_notifications.begin(); iter != m_notifications.end(); iter++)
		{
			iter->draw(window);
		}
	}
}

void AchievementManager::roomOver(){
	m_roomComplete = false;
	m_numberOfSteps = 0;
	m_noOfPickups = 0;
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

void AchievementManager::setTutorialComplete(bool arg){
	m_tutorialComplete = arg;
}

void AchievementManager::incrementPowerups(){
	m_noOfPickups++;
}

void AchievementManager::setGameMode(SceneID arg){
	m_currentScene = arg;
}

void AchievementManager::setAttempts(int arg){
	m_currAttempts = arg;
}

void AchievementManager::setTime(float arg){
	m_currTime = arg;
}

void AchievementManager::setFont(sf::Font* font){
	m_font = font;
}

int AchievementManager::getHighScore() const {
	return m_highScore;
}

int AchievementManager::getTimedHighScore() const{
	return m_timedHighScore;
}

int AchievementManager::getCurrScore() const{
	return m_currScore;
}

void AchievementManager::setCurrScore(int arg) {
	m_currScore = arg;
	if (arg > m_highScore)
		m_highScore = arg;
}

void AchievementManager::setTimedCurrScore(int arg){
	m_currScore = arg;
	if (arg > m_timedHighScore)
		m_timedHighScore = arg;
}
