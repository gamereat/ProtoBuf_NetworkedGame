#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
class ServerController
{
public:
	ServerController();
	~ServerController();

	/*
	Init the client setting up all objects

	returns if init has been succefull and can continue

	*/
	bool Init();
	/*
	Updates the all the game information

	@return if game is stil running
	- True game is still playing
	- False game is ended
	*/
	bool Update();
private:
	
	/*
	The version number of the server
	*/
	int versionNumber;

	/*
	expected version number for clients connecting to the server
	*/
	int clientVNumExpected;


	/*
	Font used thought the game
	*/
	sf::Font standardFont;



	/*
	Contains the version number of the build to be displayed on screen
	*/
	sf::Text clientVersionNumberText;

	/*
	Contains the version number of the server to be displayed on screen
	*/
	sf::Text severVersionNumberText;
	  
	/*
	Game clock used to caculate delta Time
	*/
	sf::Clock deltaTimeClock;

	/*
	Delta time from the game
	*/
	float deltaTime;
};

