#include "Player.h"



Player::Player()
{
}

Player::Player(int score, sf::Vector2f pos) 
{
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

void Player::UpdatePlayer(ClientMessage::Playerinfromation* playerInfo)
{
	playerNumber = playerInfo->playernumber();

	ClientMessage::playerPos playerpos = playerInfo->pos();
	position = sf::Vector2f(playerpos.posx(), playerpos.posy());
 

}
