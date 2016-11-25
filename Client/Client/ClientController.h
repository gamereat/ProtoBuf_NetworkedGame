#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "GameLogging.h"
#include "NetworkManager.h"
 /**
*	Controls the client interaction though the game 
*	
*/
class ClientController
{
public:
	
	/*
	* Current State for the client during gameplay
	*/
	enum class ClientGameState
	{
		Init = 0,
		Menu = 1,
		ReadyToPlay = 2,
		Playing = 3,
		GameOver = 4
		
	};


	
	ClientController();
	~ClientController();

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

	/*
	Renderes any images from the screen

	@param RenderWindow		The window being used for the scene
	*/
	void Render(sf::RenderWindow* renderWindow);

//	void setPlayerType();

private: 

	/*
	Controls network connections for game
	*/
	NetworkManager networkManager;
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
	The current client game state thoughout the users play though 
	*/
	ClientGameState currentClientGameState;

	/*
	Holds the current Version number of the client loaded in from file and used to check agaist the server 
	*/
	int clientVersionNumber;

	/*
	Game clock used to caculate delta Time
	*/
	sf::Clock deltaTimeClock;

	/*
	Delta time from the game
	*/
	float deltaTime;

	
};

