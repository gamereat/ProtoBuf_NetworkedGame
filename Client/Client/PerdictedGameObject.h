#pragma once
#include "GameObject.h"


// number of prevous pos to keep on record at any given point 
const int PREVOUS_POS_TO_RECORD = 4;


class PerdictedGameObject :
	public GameObject
{
public:
	PerdictedGameObject();
	~PerdictedGameObject();


	virtual void Update(float deltaTime);

protected:

	/*
	Cacaulates the perdicted new posistion of the ball
	*/
	void CacaulatePerdictedPos();


	std::vector<sf::Vector2f> prevousPosition;

	std::vector<int> prevousMessageTimes;

	int timeOfLastUpdate;


	sf::Vector2f perdictedPos;


	int estimateLag;

};

