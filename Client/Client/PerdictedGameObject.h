#pragma once
#include "GameObject.h"

class PerdictedGameObject :
	public GameObject
{
public:
	PerdictedGameObject();
	~PerdictedGameObject();


	virtual void Update(float deltaTime);

	virtual void Init();
protected:

	/*
	Cacaulates the perdicted new posistion of the ball
	*/
	void CacaulatePerdictedPos();




	sf::Vector2f perdictedPos;


	std::vector<sf::Vector2f> prevousPosition;

	std::vector<int> prevousMessageTimes;

	std::vector<int> timeOfLastUpdate;

	std::vector<sf::Vector2f> prevousVelocity;

	sf::Vector2f	lasteUpdatePosition;

	sf::Texture paddleTexture;

	int currentScore;

	int playerNumber;

	int estimateLag;


	int gameTimeAtLastUpdate;

};

