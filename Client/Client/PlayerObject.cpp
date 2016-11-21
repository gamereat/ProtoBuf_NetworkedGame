#include "PlayerObject.h"



PlayerObject::PlayerObject()
{
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::Init()
{
	// Set a default sprite 
	sprite.setColor(sf::Color(255, 0, 0, 255));
}

void PlayerObject::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(sprite);
}

void PlayerObject::HandleInput(float deltaTime)
{
	// Work out the player movement informaton on the current client
	playerMovement(deltaTime);
}


void PlayerObject::Update(float deltaTime)
{
	HandleInput(deltaTime);
}

void PlayerObject::playerMovement(float deltaTime)
{
	// Gets all the four directional movmenet and move the player accordingly
	// change the direction of the sprite
	if (sf::Keyboard::isKeyPressed(playerControlls.getUpMovementKey()))
	{
		sprite.move(0.0f, playerSpeed * deltaTime);
		playerDirection = PlayerDirection::Up;
	}
	if (sf::Keyboard::isKeyPressed(playerControlls.getDownpMovementKey()))
	{
		sprite.move(0.0f, -playerSpeed * deltaTime);
		playerDirection = PlayerDirection::Down;

	}
	if (sf::Keyboard::isKeyPressed(playerControlls.getLeftMovementKey()))
	{
		sprite.move(-playerSpeed * deltaTime, 0.0f);
		playerDirection = PlayerDirection::Left;

	}
	if (sf::Keyboard::isKeyPressed(playerControlls.getRightMovementKey()))
	{
		sprite.move(playerSpeed *deltaTime ,0.0f);
		playerDirection = PlayerDirection::Right;

	} 
}
