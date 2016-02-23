#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"
#include "AchievementManager.h"

class GameOverScene : public Scene {
public:
	GameOverScene(sf::Font * font, std::string label, SceneID id);
	~GameOverScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();
private:
	sf::Sprite m_sprBackground;
	sf::Texture * m_backgroundTex;
	sf::Text m_label;
	sf::Text m_ScoreLabel;
	SceneID m_cameFrom;
};

#endif