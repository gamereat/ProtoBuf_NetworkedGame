#pragma once
#include "GameObject.h"

// number of prevous pos to keep on record at any given point 
const int PREVOUS_POS_TO_RECORD = 2;


class PridictedGameObject : public GameObject
{
public:
	PridictedGameObject();
	~PridictedGameObject();

	void Update();

protected:



	sf::Vector2f perdictedPos;


	std::vector<sf::Vector2f> prevousPosition;


 
	std::vector<int> timeOfLastUpdate;

	std::vector<sf::Vector2f> prevousVelocity;

	void CacaulatePerdictedPos();

	   
	int estimateLag;
	 



};

