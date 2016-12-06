#include "PridictedGameObject.h"
#include "StaticMathsLib.h"
#include "NetworkTimeStart.h"

PridictedGameObject::PridictedGameObject()
{
	// add some init messages so can look back on prevus pos 
	for (int i = 0; i < PREVOUS_POS_TO_RECORD; i++)
	{
		predictionInfo newInfo;

		newInfo.acceleration = 0;
		newInfo.messageNumber = 0;
		newInfo.pos = sf::Vector2f(0, 0);
		newInfo.timeOfUpdat = 0;
		newInfo.velocity = sf::Vector2f(0, 0);

		messageData.push_back(newInfo);
	}
}


PridictedGameObject::~PridictedGameObject()
{
}

void PridictedGameObject::UpdateMessageInfo(sf::Vector2f newPos, int gameTime, int messageNumber)
{
	if (messageData.size() > 0)
	{
		// got a old messsage
		if (messageData.end()[-1].messageNumber >= messageNumber)
		{
			return;
		}

		predictionInfo info;

		info.messageNumber = messageNumber;


		lasteUpdatePosition = newPos;


		info.pos = lasteUpdatePosition;




		gameTimeAtLastUpdate = NetworkTimeStart::gameTime - estimateLag;

		info.timeOfUpdat = NetworkTimeStart::gameTime - estimateLag;

		sf::Vector2f velocity;
		sf::Vector2f distance;


		distance.x = messageData.end()[-1].pos.x - messageData.end()[-2].pos.x;
		distance.y = messageData.end()[-1].pos.y - messageData.end()[-2].pos.y;


		float tDistance = sqrt(distance.x * distance.x + distance.y * distance.y);

		if (tDistance == 0)
		{

			info.velocity = sf::Vector2f(0, 0);
		}
		else
		{
			sf::Vector2f unitVelocity = sf::Vector2f((distance.x / tDistance), (distance.y / tDistance));

			velocity.x = 0;
			velocity.y = distance.y / messageData.end()[-1].timeOfUpdat - messageData.end()[-2].timeOfUpdat;

			info.velocity = velocity;
		}






		messageData.push_back(info);
	}
}

void PridictedGameObject::UpdateMessageInfo(sf::Vector2f newPos, sf::Vector2f velocity,  int messageNumber)
{
	if (messageData.size() > 0)
	{
		// got a old messsage
		if (messageData.end()[-1].messageNumber >= messageNumber)
		{
			return;
		}

		predictionInfo info;

		info.messageNumber = messageNumber;


		lasteUpdatePosition = newPos;


		info.pos = lasteUpdatePosition;




		gameTimeAtLastUpdate = NetworkTimeStart::gameTime - estimateLag;

		info.timeOfUpdat = NetworkTimeStart::gameTime - estimateLag;


		info.velocity = velocity;





		messageData.push_back(info); 
	}
}

void PridictedGameObject::CacaulatePerdictedPos()
{
	if (messageData.size() == PREVOUS_POS_TO_RECORD)
	{
		perdictedPos = lasteUpdatePosition;
		return;

	}
	// Using Cubic Splines

	// Will use the last 3 cords recived to work out next one 

	// multiply this by the lag caculated by the server

	//Cubic Bézier curves

	//	(1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * P2 + t^3 * P3 ;    0 < t < 1;


	// Time since last packet info
	float gameTime = (float)NetworkTimeStart::gameTime - estimateLag;


	sf::Vector2f lastPrePath = messageData.end()[-2].pos - messageData.end()[-3].pos;

	float lastDTime = messageData.end()[-2].timeOfUpdat - messageData.end()[-3].timeOfUpdat;

	float startDTime = messageData.end()[-1].timeOfUpdat - messageData.end()[-3].timeOfUpdat;

	sf::Vector2f lastVelocity = lastPrePath / lastDTime;

	sf::Vector2f startPos = messageData.end()[-3].pos + startDTime * lastVelocity;

	float currentDTime = gameTime - messageData.end()[-1].timeOfUpdat;

	sf::Vector2f predicPath = messageData.end()[-1].pos - messageData.end()[-2].pos;

	float dTime = messageData.end()[-1].timeOfUpdat - messageData.end()[-2].timeOfUpdat;

	sf::Vector2f endpos = messageData.end()[-1].pos + currentDTime *	predicPath / dTime;

	sf::Vector2f linearConvergence = endpos - startPos;

	float velocity = linearConvergence.y / dTime;

	perdictedPos.y = startPos.y + currentDTime * velocity;

	perdictedPos.x = messageData.end()[-1].pos.x;


	//}

	//	perdictedPos.y = messageData.end()[-1].velocity.y * messageData.end()[-1].pos.y *( messageData.end()[-2].timeOfUpdat - messageData.end()[-1].timeOfUpdat);




}
