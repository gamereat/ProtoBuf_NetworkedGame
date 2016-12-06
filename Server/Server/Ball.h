#pragma once
#include "GameObject.h"
#include "Player.h"
#include "ServerController.h"

/*
Maxium valocity Ball can get 
*/
const float MAX_STARTING_VELOCITY = 250;
/*
Minimum ball speed 
*/
const float MIN_STARTING_VELOCITY = 75;

/*
Results of a ball collision detection
*/
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

	/*
	Overload constructor 

	@param velocity		The velocity ball will start at
	@param startPos		Starting position of the ball
	*/
	Ball(sf::Vector2f velocity, sf::Vector2f startPos);
	~Ball();

	/*
	Init ball settings
	*/
	void Init();

	/*
	Update Ball state 

	@param deltaTime	delta from from update
	*/
	void Update(float deltaTime);


	/*
	Restarts ball and starts at new velocity
	*/
	void Restart();
	
	/*
	Get the velocity of the ball
	@return		Current velocity of ball
	*/
	sf::Vector2f getVelocity();

	/*
	Sets a new velocity for the ball

	@param velocity		New velocity for ball
	*/
	void setVelocity(sf::Vector2f velocity);


	/*
		Test collisions for the state

		@param players[NUM_PLAYERS]		An array with all the playesr within the game
	*/
	BallCollionResults CollisionDetection(Player* players[NUM_PLAYERS] );


	/*
	set the game to start
	*/
	void SetToStart();

private:


	
	/*
	Caculate a random velocity for the ball to start going at 

	@returns	vector contraining velocity in x and y direction for ball to travel in
	*/
	sf::Vector2f ChoiceRandomStartingVelocity();
	
	/*
	Velocity the ball is current firing at 
	*/
	sf::Vector2f velocity;

 
	/*
	Texture applied to ball
	*/
	sf::Texture ballTexture;
};

