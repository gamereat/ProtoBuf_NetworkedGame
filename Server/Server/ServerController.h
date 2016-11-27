#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "NetworkManager.h"
#include "Player.h"
#include "Map.h"
/*
Number of players within a game
*/
const int NUM_PLAYERS = 4;
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
	void Render(sf::RenderWindow * renderWindow);
	/*
	Updates the all the game information

	@return if game is stil running
	- True game is still playing
	- False game is ended
	*/
	bool Update();
private:
	
	/*
	Synced up map used to dispaly to players
	*/
	Map* gameMap;

	/*
	players in the game
	*/
	Player* players[4];

	/*
	Manages all the nwtwork conections
	*/
	NetworkManager networkManger;


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

	/*
	Players the server is talking with
	*/
	int playersInGame;
};

