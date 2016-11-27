#include "SFML\Graphics.hpp"
#include "NetworkManager.h"
#include <iostream>
#include "ServerController.h";
#include "GameLogging.h"
void main()
{
 	sf::RenderWindow window(sf::VideoMode(800, 600), "Pac Man Server");
	ServerController serverController;
	GameLogging::Log("----------- INIT STATED ----------");

	serverController.Init();



		GameLogging::Log("----------- INIT COMPLETE ----------");


		GameLogging::Log("----------- UPDATE LOOP STARTED ----------");

		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
 
			serverController.Update();
			serverController.Render(&window);

			window.display();
		}

		GameLogging::Log("----------- APPLICATION ENDING ----------");



	// Holds so log's can be looked at 
	std::cin.get();
 
}