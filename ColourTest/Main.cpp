//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#include "Tile.h"
#include "Player.h"
#include "TileManager.h"
#include <ctime>
#include "SceneManager.h"
#include "SoundManager.h"

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
	window.setPosition(sf::Vector2i(0, 0));
	srand(time(0));

	SceneManager::getInstance();

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		SceneManager::getInstance()->update(&Event, &window);
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::KeyPressed)
			{
				
			}
		}

		//prepare frame
		window.clear(sf::Color(40, 40, 50));

		//draw frame items
		SceneManager::getInstance()->draw(&window);

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}
