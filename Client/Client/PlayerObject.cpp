#include "PlayerObject.h"



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
	playerSpeed = 100;
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
	
	setPosition(sf::Vector2f(playerInfo.pos().posx(), playerInfo.pos().posy()));

}

float PlayerObject::getPlayerSpeed()
{
	return playerSpeed;
}

void PlayerObject::setPlayerSpeed(float playerSpeed)
{
	this->playerSpeed = playerSpeed;
}

ClientMessage::Playerinfromation::PlayerType PlayerObject::getPlayerType()
{
	return playerType;
}

void PlayerObject::setPlayerType(ClientMessage::Playerinfromation::PlayerType playerType)
{
	this->playerType = playerType;
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
		if (sf::Keyboard::isKeyPressed(playerControlls.getLeftMovementKey()))
		{
			sprite.move(-playerSpeed * deltaTime, 0.0f);
			playerDirection = PlayerDirection::Left;

		}
		if (sf::Keyboard::isKeyPressed(playerControlls.getRightMovementKey()))
		{
			sprite.move(playerSpeed *deltaTime, 0.0f);
			playerDirection = PlayerDirection::Right;

		}
	}
}
