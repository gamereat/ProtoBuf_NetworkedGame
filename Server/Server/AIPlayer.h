#pragma once
#include "Player.h"
#include "Ball.h"
const int MAX_PADDLE_SPEED = 350;
class AIPlayer :
	public Player
{
public:
	AIPlayer();
	~AIPlayer();

	void Update(float delataTime);

	void setBall(Ball* ball);
private:

	Ball* ball;

	void CaculateAIPos(float delataTime);



};

