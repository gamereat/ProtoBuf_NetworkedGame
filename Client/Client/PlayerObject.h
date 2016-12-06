#pragma once
#include "GameObject.h"
#include ".././../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"

const int PADDLE_SPEED = 350;

// How the player will be able to move
// Allows for rebuinding of keys if needed 
 struct playerControls
{
public:

	/*
	Set of default controls
	*/
	playerControls()
	{
 
		upMovementKey = sf::Keyboard::Up;
		downMovementKey = sf::Keyboard::Down;
		rightMovementKey = sf::Keyboard::Right;
		leftMovementKey = sf::Keyboard::Left;
	 
	}

	/*
	overload contructor to allow for 2 players
	it will give each player diffrent controlls

	@param isSecondPlayer	if the player is first or secodn player
	*/
	playerControls(bool isSecondPlayer)
	{
		if (!isSecondPlayer)
		{
			// sets the default contorls 
			upMovementKey = sf::Keyboard::W;
			downMovementKey = sf::Keyboard::S;
			rightMovementKey = sf::Keyboard::D;
			leftMovementKey = sf::Keyboard::A;
		}
		else
		{
			upMovementKey = sf::Keyboard::Up;
			downMovementKey = sf::Keyboard::Down;
			rightMovementKey = sf::Keyboard::Right;
			leftMovementKey = sf::Keyboard::Left;
		}
	}


	// get key bound to up movement
	inline sf::Keyboard::Key getUpMovementKey()
	{
		return upMovementKey;
	}

	// get key bound to down movement
	inline sf::Keyboard::Key getDownpMovementKey()
	{
		return downMovementKey;
	}

	//get key bound to left moment 
	inline sf::Keyboard::Key getLeftMovementKey()
	{
		return leftMovementKey;
	}

	//ge key bound to right movememnet 
	inline sf::Keyboard::Key getRightMovementKey()
	{
		return rightMovementKey;
	}

private:
	// Basic control information
	sf::Keyboard::Key upMovementKey;
	sf::Keyboard::Key downMovementKey;
	sf::Keyboard::Key leftMovementKey;
	sf::Keyboard::Key rightMovementKey;



};

 /*
 Default player object 
 */
class PlayerObject :
	public GameObject
{
public:

	enum class PlayerDirection
	{
		Up = 0,
		Down = 1,
		Left = 2,
		Right = 3
	};


	
	PlayerObject();
	~PlayerObject();
	virtual void Render(sf::RenderWindow* renderWindow);
	virtual void Init();
	virtual void Update(float deltaTime);

	/*
	Updates the given palyer with the player information
	*/
	void UpdatePlayerInfo(ServerMessage::Playerinfromation);

	float getPlayerSpeed();
	void setPlayerSpeed(float playerSpeed);
	 ;

	int getCurrentScore();
	void setCurrentScore(int currentScore);

	int getPlayerNumber();
	void setPlayerNumber(int playerNum);

	void setIsControllable(bool isControllable);

	void setPlayerControls(bool isSecondPlayer);

	sf::Vector2f  getPosition();
	void setPosition(sf::Vector2f);

protected:


	/*
	Handles any input from the player 
	*/
	virtual void HandleInput(float deltaTime);

	 
	/*
	The speed the user can move at
	*/
	float playerSpeed;


	/*
	The current score the player has achived
	*/
	int currentScore;


private:
	// Will caculate all the momement information
	void playerMovement(float deltaTime);

 

	// Holds the controls for the player
	playerControls playerControlls;
	
	/*
	The current Direction the player is facing
	*/
	PlayerDirection playerDirection;


	/*
	The player number within the game. Assigend by the server
	*/
	int playerNumber;

	/*
	If the player is controllable
	*/
	bool isControllable;

	
};

