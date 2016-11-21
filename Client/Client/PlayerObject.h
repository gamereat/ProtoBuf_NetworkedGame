#pragma once
#include "GameObject.h"
class PlayerObject :
	public GameObject
{
public:

	// How the player will be able to move
	struct playerControls
	{
	public:

		playerControls()
		{
			// sets the default contorls 
			upMovementKey = sf::Keyboard::W;
			downMovementKey = sf::Keyboard::S;
			rightMovementKey = sf::Keyboard::D;
			leftMovementKey = sf::Keyboard::A;
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

	enum class PlayerDirection
	{
		Up = 0,
		Down = 1,
		Left = 2,
		Right = 3
	};

	enum PlayerState
	{

	};
	
	/*
	The type of player that the user is controlling
	*/
	enum class PlayerType
	{
		Pac = 0,
		Ghost = 1
	};
	
	PlayerObject();
	~PlayerObject();
	virtual void Render(sf::RenderWindow* renderWindow);
	virtual void Init();
	virtual void Update(float deltaTime);
protected:

	virtual void HandleInput(float deltaTime);

	
	/*
	The Player type being controlled by the player
	*/
	PlayerType playerType;

	/*
	The speed the user can move at
	*/
	float playerSpeed;

private:
	// Will caculate all the momement information
	void playerMovement(float deltaTime);

	// Holds the controls for the player
	playerControls playerControlls;
	
	/*
	The current Direction the player is facing
	*/
	PlayerDirection playerDirection;
	
};

