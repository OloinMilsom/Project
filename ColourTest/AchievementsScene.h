#ifndef ACHIEVEMENTSSSCENE_H
#define ACHIEVEMENTSSSCENE_H

#include "Scene.h"
#include "AchievementManager.h"

class AchievementsScene : public Scene{
public:
	AchievementsScene(sf::Font* font);
	~AchievementsScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();

private:
	int m_currentScreen;
	sf::Sprite m_sprBackground;
	std::vector<std::pair<sf::RectangleShape, sf::Text>> m_achievements;
};

#endif