#include "SFML\Graphics.hpp"
 #include <iostream>
#include "ServerController.h";
#include "GameLogging.h"

 void main()
{  
	

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT ), "Pong Server - ALAN YEATS 1402402");
	ServerController serverController;

	GameLogging::Log("----------- INIT STATED ----------");

	serverController.Init();

 
		GameLogging::Log("----------- INIT COMPLETE ----------");


		GameLogging::Log("----------- UPDATE LOOP STARTED ----------");

		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color(0, 0, 124, 255));

  
			serverController.Update();
			serverController.Render(&window);

			window.display();
		}

		GameLogging::Log("----------- APPLICATION ENDING ----------");



	// Holds so log's can be looked at 
	std::cin.get();
 
}




 