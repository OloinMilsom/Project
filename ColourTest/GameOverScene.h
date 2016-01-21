#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"

class GameOverScene : public Scene {
public:
	GameOverScene(sf::Font * font, std::string label, SceneID id);
	~GameOverScene();
	void update(sf::Event* e, sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void start();
	void stop();
private:
	sf::Text m_label;
	SceneID m_cameFrom;
};

#endif