#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:
	Ball();
	Ball(sf::Vector2f velocity, float angle, sf::Vector2f startPos);
	~Ball();



	float getAngle();
	void setAngle(float angle);


	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);
private:

	/*
	Velocity the ball is current firing at 
	*/
	sf::Vector2f velocity;


	/*
	Angle the ball is cuurently at
	*/
	float angle;
};

