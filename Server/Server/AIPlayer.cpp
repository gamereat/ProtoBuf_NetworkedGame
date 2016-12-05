#include "AIPlayer.h"



AIPlayer::AIPlayer()
{
}


AIPlayer::~AIPlayer()
{
}

void AIPlayer::Update(float delataTime)
{
	CaculateAIPos(delataTime);
}

void AIPlayer::setBall(Ball * ball)
{
	this->ball = ball;
}

void AIPlayer::CaculateAIPos(float delataTime)
{
	sf::Vector2f ballPos = ball->getPosition();


	// find diffrence in pos of ball an bat 

	float dif = sprite.getPosition().y - ballPos.y;

	int direction = (dif > 0) ? -1 : 1;


	// move towards ball
	sprite.move(0, PADDLE_SPEED * delataTime * direction);

}
