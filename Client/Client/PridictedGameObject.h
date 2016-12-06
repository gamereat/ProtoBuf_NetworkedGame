#pragma once
#include "GameObject.h"


// number of prevous pos to keep on record at any given point 
const int PREVOUS_POS_TO_RECORD = 4;



/*
Stuct used to help predict future movment information
*/
struct predictionInfo
{
	int messageNumber;
	sf::Vector2f pos;
	sf::Vector2f velocity;
	int timeOfUpdat;
	float acceleration;

};

class PridictedGameObject : public GameObject
{
public:
	PridictedGameObject();
	~PridictedGameObject();


protected:

	/*
	Addeds new game infromation from a new message being recieved

	@param newPos	the new pos that has been down
	@param gameTime	the time the message was recived at
	*/
	void UpdateMessageInfo(sf::Vector2f newPos, int gameTime, int messageNumber);

	/*
	Addeds new game infromation from a new message being recieved

	@param newPos	the new pos that has been down
	@param gameTime	the time the message was recived at
	*/
	void UpdateMessageInfo(sf::Vector2f newPos, sf::Vector2f velocity, int messageNumber);

	/*
	Message information recived recently
	*/
	std::vector<predictionInfo> messageData;

	/*
	The current predicted pos
	*/
	sf::Vector2f perdictedPos;

	/*
	Caculates the new prected position
	*/
	void CacaulatePerdictedPos();

	/*
	esimate lag for the object
	*/
	int estimateLag;


	/*
	time the last game object was updated
	*/
	int gameTimeAtLastUpdate;


};

