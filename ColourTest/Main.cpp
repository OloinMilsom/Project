//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#include "Tile.h"
#include "Player.h"
#include "TileManager.h"
#include <ctime>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>



////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "ColourTest");

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	srand(time(0));

	TileManager::getInstance()->initialise(5);

	Player * player = new Player(0, TileManager::getInstance()->getSize() / 2);
	player->addColour(TileManager::getInstance()->getStartColor());
	player->goalFinder();

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if (Event.type == sf::Event::KeyPressed) {
				if (Event.key.code == sf::Keyboard::Escape)
					window.close();
				if (Event.key.code == sf::Keyboard::W)
				{
					player->move(Player::direction::UP);
				}
				else if (Event.key.code == sf::Keyboard::A)
				{
					player->move(Player::direction::LEFT);
				}
				else if (Event.key.code == sf::Keyboard::S)
				{
					player->move(Player::direction::DOWN);
				}
				else if (Event.key.code == sf::Keyboard::D)
				{
					player->move(Player::direction::RIGHT);
				}
				else if (Event.key.code == sf::Keyboard::R)
				{
					TileManager::getInstance()->resetRoom();
					player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
					player->resetColour();
				}
				else if (Event.key.code == sf::Keyboard::F)
				{
					if (player->getPos() == sf::Vector2f(TileManager::getInstance()->getSize(), TileManager::getInstance()->getSize() / 2)){
						player->resetColour();
						TileManager::getInstance()->initialise(TileManager::getInstance()->getSize());
						player->setPos(sf::Vector2f(0, TileManager::getInstance()->getSize() / 2));
						player->goalFinder();
						player->setPos(sf::Vector2f(-1, TileManager::getInstance()->getSize() / 2));
					}
				}
			}
		}

		//prepare frame
		window.clear(sf::Color(40, 40, 50));

		//draw frame items
		for (int y = 0; y < TileManager::getInstance()->getSize(); y++)
		{
			for (int x = 0; x < TileManager::getInstance()->getSize(); x++)
			{
				window.draw(TileManager::getInstance()->getDrawAt(x, y));
			}
		}
		window.draw(TileManager::getInstance()->getStartDraw());
		window.draw(TileManager::getInstance()->getFinishDraw());

		/*sf::RectangleShape rect(sf::Vector2f(100, 100));
		rect.setFillColor(player->getColour());
		window.draw(rect);*/
		sf::CircleShape circ((500 / TileManager::getInstance()->getSize()) * 0.5f);
		circ.setPosition(sf::Vector2f(player->getPos().x * (500 / TileManager::getInstance()->getSize()) + 150, player->getPos().y * (500 / TileManager::getInstance()->getSize())));
		circ.setFillColor(sf::Color(100,100,100));
		window.draw(circ);
		sf::RectangleShape r(sf::Vector2f(40, 40));
		r.setFillColor(player->getColour());
		window.draw(r);

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}