#pragma once
#include "GameObject.h"
#include ".././../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"

const int PADDLE_SPEED = 100;

// How the player will be able to move
// Allows for rebuinding of keys if needed 
 struct playerControls
{
public:
	playerControls()
	{
 
		upMovementKey = sf::Keyboard::Up;
		downMovementKey = sf::Keyboard::Down;
		rightMovementKey = sf::Keyboard::Right;
		leftMovementKey = sf::Keyboard::Left;
	 
	}

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

	inline sf::Keyboard::Key getUpMovementKey()
	{
		return upMovementKey;
	}
	inline sf::Keyboard::Key getDownpMovementKey()
	{
		return downMovementKey;
	}
	inline sf::Keyboard::Key getLeftMovementKey()
	{
		return leftMovementKey;
	}
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

