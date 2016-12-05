#include "SFML\Graphics.hpp"
#include "NetworkManager.h"
#include <iostream>
#include "ServerController.h";
#include "GameLogging.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <http_client.h>
#include <filestream.h>
#include <iostream>
#include <sstream>

using namespace web::http;
using namespace web::http::client;
void main()
{  

	sf::Http::Request request;

	// fill the request...
	//request.setUri("/name");
	//request.setHttpVersion(1, 1); // HTTP 1.1
	//request.setField("Content-Type", "application/text");


	request.setMethod(sf::Http::Request::Get);

	 



	// send the request
	sf::Http http("http://localhost:8001/");
	sf::Http::Response response = http.sendRequest(request);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT ), "Pac Man Server");
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




 