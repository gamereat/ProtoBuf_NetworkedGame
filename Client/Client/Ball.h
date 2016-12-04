#pragma once
#include "PerdictedGameObject.h"

#include "../ProtroHeaders/ServerMessage.pb.h"
class Ball : public PerdictedGameObject
{
public:
	Ball();
	Ball(sf::Vector2f velocity, float angle, sf::Vector2f startPos);
	~Ball();


	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow*);

	float getAngle();

 
	/*
	Update ball based on ball info
	*/
	void UpdateBallInfo(ServerMessage::BallInformation ballnfo);
	sf::Vector2f getVelocity();
private:


 
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

