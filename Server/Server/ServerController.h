#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

const int NUM_PLAYERS = 2;

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 800;
const int PADDLE_SPEED = 100;
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
	The text for the user score 
	*/
	sf::Text userScoreText;


	/*
	The text for AI Score
	*/
	sf::Text AIScoreText;
	/*
	Ball used to hit around by players
	*/
	class Ball* ball;

	sf::Clock networkUpdateTimer;

 
	/*
	time (IN SECONDS) between new message being sent the clients
	*/
	float clientNetworkUpdateTime;

	void createClientMessage();
 
	/*
	players in the game
	*/
	class Player* players[NUM_PLAYERS];


	/*
	AI player which is against player
	*/
	class AIPlayer* aiPlayer;

	/*
	Manages all the nwtwork conections
	*/
	class NetworkManager* networkManger;


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

