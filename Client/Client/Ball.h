#pragma once
#include "PridictedGameObject.h"

#include "../ProtroHeaders/ServerMessage.pb.h"

/*
Ball object inherits from pridected object as predicts pos.
*/
class Ball : public PridictedGameObject
{
public:
	Ball();

	/*
	Overload constructor

	@param velocity		The velocity ball will start at
	@param startPos		Starting position of the ball
	*/
	Ball(sf::Vector2f velocity, sf::Vector2f startPos);
	~Ball();


	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render(sf::RenderWindow*);

 
	/*
	Update ball based on ball info
	*/
	void UpdateBallInfo(ServerMessage::BallInformation ballnfo, int messageNumber);

	/*
	Gets velocty of the ball
	*/
	sf::Vector2f getVelocity();

	/*
	Restarts ball and starts at new velocity
	*/
	void Restart();

private:


 
	/*
	Velocity the ball is current firing at 
	*/
	sf::Vector2f velocity;

	 

	/*
	Texture applied to ball
	*/
	sf::Texture ballTexture;

};

