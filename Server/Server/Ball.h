#pragma once
#include "GameObject.h"
#include "Player.h"
#include "ServerController.h"
const float MAX_STARTING_VELOCITY = 250;
const float MIN_STARTING_VELOCITY = 75;
enum BallCollionResults
{
	None,
	HitBat,
	HitTopBottom,
	PlayerOneScore,
	PlayerTwoScore,

};
class Ball : public GameObject
{
public:



	Ball();
	Ball(sf::Vector2f velocity, float angle, sf::Vector2f startPos);
	~Ball();

	void Init();
	void Update(float deltaTime);

	void Restart();
	float getAngle();
	void setAngle(float angle);


	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);

	BallCollionResults CollisionDetection(Player* players[NUM_PLAYERS] );
private:


	sf::Vector2f ChoiceRandomStartingVelocity();
	/*
	Velocity the ball is current firing at 
	*/
	sf::Vector2f velocity;


	/*
	Angle the ball is cuurently at
	*/
	float angle;

	/*
	Texture applied to ball
	*/
	sf::Texture ballTexture;
};

