#pragma once


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


private:

	/*
	The current client game state thoughout the users play though 
	*/
	ClientGameState currentClientGameState;

};

