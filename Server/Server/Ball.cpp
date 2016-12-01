#include "Ball.h"



Ball::Ball()
{
}

Ball::Ball(sf::Vector2f velocity, float angle, sf::Vector2f startPos)
{
	this->velocity = velocity;
	this->angle = angle;
	setPosition(startPos);
}


Ball::~Ball()
{
}



float Ball::getAngle()
{
	return angle;
}

void Ball::setAngle(float angle)
{
	this->angle = angle;
}

sf::Vector2f Ball::getVelocity()
{
	return velocity;
}

void Ball::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}
