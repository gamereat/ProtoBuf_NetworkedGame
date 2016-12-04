#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "GameLogging.h"
#include "NetworkManager.h"
#include "Paddle.h"
#include ".././../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include ".././../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "Ball.h"
#include "Menu.h"
#include "ConnectToServer.h"
const int NUM_PLAYERS = 2;
const sf::Vector2f SCREEN_SIZE = sf::Vector2f(800, 600);
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
		ConnectToServer = 2,
		ReadyToPlay = 3,
		Playing = 4,
		GameOver = 5
		
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


	/*
	Disconect from the game server
	*/
	void Disconect();

	
	void setWindow(sf::Window*);

private: 
	


	ConnectToServer* connectToServer;

	sf::Window* window;

	Menu* menu;

	Ball* ball;

	sf::Text readToPlayText;

 	/*
	Updates ball from serverlocation
	*/
	void UpdateBall(ServerMessage::BallInformation ballInfo);

	/*
		Will connect to game server and get data from it 
	*/
	void connectToGameSever();

	/*
	Gathers current player infromation into message able to send to server
	
	@returns the current player information
	*/
	ClientMessage::Playerinfromation* GetPlayerInfo();

 
	/*
	Gathers information form client and sends it to the server 
	*/
	void UpdateGameToServer();
	/*
	Called to update game information from the server messages
	*/
	void UpdateGameFromServer();
 


	/*
	Update player location and data from the server
	*/
	void UpdatePlayers(ServerMessage::Playerinfromation players[NUM_PLAYERS]);

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
	Contains the version number of the build to be displayed on screen
	*/
	sf::Text clientNumberText;

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

	/*
	Pointer to the player that the client is controlling
	*/
	PlayerObject* controllingPlayer;
	

	/*
	The message number from the server last recived
	*/
	int lastSeverMessageRecived;
	
	/*
	The paddles used to hit the ball around 
	only one is controlled by each client 
	*/
	Paddle* paddle[NUM_PLAYERS];

	sf::Clock networkUpdateTimer;


	/*
	time (IN SECONDS) between new message being sent the clients
	*/
	float serverNetworkUpdateTime;

	int frameToConnect;

	bool connectedToServer;
};

