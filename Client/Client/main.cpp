#include "SFML\Graphics.hpp"
#include "ClientController.h"
#include <iostream>
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "google\protobuf\message.h"

#include "GameLogging.h"
int main()
{

	ClientController clientController;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pong client - Alan Yeats 1402402");

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
			while (window.pollEvent(event) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color(0, 0, 124, 255));

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

	clientController.Disconect();
	// Holds so log's can be looked at 
	std::cin.get();

	//close downb 
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
 