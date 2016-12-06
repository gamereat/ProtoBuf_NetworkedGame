#include "PlayerObject.h"
#include "GameLogging.h"


PlayerObject::PlayerObject()
{
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::Init()
{
	isControllable = false;
	// Set a default sprite 
	sprite.setColor(sf::Color(255, 0, 0, 255));

	playerNumber = -1;
	playerSpeed = PADDLE_SPEED;
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

void PlayerObject::UpdatePlayerInfo(ServerMessage::Playerinfromation playerInfo)
{
	currentScore = playerInfo.playerscore();
	
	setPosition(sf::Vector2f(playerInfo.possition().posx(), playerInfo.possition().posy()));

}

float PlayerObject::getPlayerSpeed()
{
	return playerSpeed;
}

void PlayerObject::setPlayerSpeed(float playerSpeed)
{
	this->playerSpeed = playerSpeed;
}
 
 

int PlayerObject::getCurrentScore()
{
	return currentScore;
}

void PlayerObject::setCurrentScore(int currentScore)
{
	this->currentScore = currentScore;
}

int PlayerObject::getPlayerNumber()
{
	return playerNumber;
}

void PlayerObject::setPlayerNumber(int playerNum)
{
	this->playerNumber = playerNum;
}

void PlayerObject::setIsControllable(bool isControllable)
{
	this->isControllable = isControllable;
}

void PlayerObject::setPlayerControls(bool isSecondPlayer)
{
	playerControlls = playerControls(isSecondPlayer);
}

void PlayerObject::playerMovement(float deltaTime)
{
	if (isControllable)
	{
		// Gets all the four directional movmenet and move the player accordingly
		// change the direction of the sprite
		if (sf::Keyboard::isKeyPressed(playerControlls.getUpMovementKey()))
		{
			sprite.move(0.0f, -playerSpeed * deltaTime);
			playerDirection = PlayerDirection::Up;
		}
		if (sf::Keyboard::isKeyPressed(playerControlls.getDownpMovementKey()))
		{
			sprite.move(0.0f, playerSpeed * deltaTime);
			playerDirection = PlayerDirection::Down;

		}
 
	}
}

sf::Vector2f PlayerObject::getPosition()
{
	//GameLogging::Log("sprite pos " + std::to_string(sprite.getPosition().y));

	return sprite.getPosition();

}

void PlayerObject::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}
