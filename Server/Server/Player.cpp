#include "Player.h"



Player::Player()
{
}

Player::Player(int score, ServerMessage::Playerinfromation::PlayerType playerType, sf::Vector2f pos) 
{
	position = pos;
	this->playerType = playerType;
	currentScore = score;
}


Player::~Player()
{
}

void Player::setScore(int newScore)
{
	currentScore = newScore;
}

int Player::getScore()
{
	return currentScore;
}

void Player::setPlayerType(ServerMessage::Playerinfromation::PlayerType mewType)
{
	playerType = mewType;
}

ServerMessage::Playerinfromation::PlayerType Player::getPlayerType()
{
	return playerType;
}
