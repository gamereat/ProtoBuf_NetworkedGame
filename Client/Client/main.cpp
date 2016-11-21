#include "SFML\Graphics.hpp"
#include "ClientController.h"
#include <iostream>
#include "GameLogging.h"
int main()
{

	ClientController clientController;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pac Man client");

	GameLogging::Log("----------- INIT STATED ----------");

 
 
	if (!clientController.Init())
	{
		GameLogging::LogError(" INIT FAILED   " );

	}
	else
	{
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

			if (clientController.Update())
			{
				clientController.Render(&window);
			}
			else
			{

				GameLogging::Log("----------- UPDATE FAILED ----------\n");
 				window.close();

			}

 
			window.display();
		}

		GameLogging::Log("----------- APPLICATION ENDING ----------");

 	}
	// Holds so log's can be looked at 
	std::cin.get();
	return 0;
}
 