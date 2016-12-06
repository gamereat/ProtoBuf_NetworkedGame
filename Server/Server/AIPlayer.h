#pragma once
#include "Player.h"
#include "Ball.h"


const int MAX_PADDLE_SPEED = 350;

/*
Simple AI Player used for debugging and testing 
will act like a normal player
*/
class AIPlayer : public Player
{
public:
	AIPlayer();
	~AIPlayer();

	/*
	Update pos and such of player
	*/
	void Update(float delataTime);

	void setBall(Ball* ball);
private:

	Ball* ball;

	/*
	Caculates the position of the bat based off ball pos and it's max speed 
	*/
	void CaculateAIPos(float delataTime);



};

