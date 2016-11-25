#include "SFML\Graphics.hpp"
#include "ClientController.h"
#include <iostream>
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "google\protobuf\message.h"

#include "GameLogging.h"
int main()
{

	ClientController clientController;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pac Man client");

	GameLogging::Log("----------- INIT STATED ----------");

 
	ClientMessage::ClientMessage newMessage; 
	//ClientMessage::ClientInformation client;
	//	ClientMessage::Playerinfromation player;
	//	ClientMessage::playerPos pos;
	//	pos.set_posx(0);
	//	pos.set_posy(0);
	//	client.set_clientversion(0);
	//	client.set_messagenumber(0);
	//	player.set_playernumber(0);
	//	player.set_type(ClientMessage::Playerinfromation_PlayerType_Ghost);
	//	player.set_allocated_pos(&pos);
	//	newMessage.set_allocated_clientinfo(&client);
	//	newMessage.set_allocated_playerinfo(&player);
 //
		std::cout << newMessage.SpaceUsed();
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

	//close downb 
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
 