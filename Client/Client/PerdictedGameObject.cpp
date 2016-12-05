#include "PerdictedGameObject.h"
#include "NetworkTimeStart.h"


PerdictedGameObject::PerdictedGameObject()
{
}


PerdictedGameObject::~PerdictedGameObject()
{
}

void PerdictedGameObject::Update(float deltaTime)
{
	CacaulatePerdictedPos();
	sprite.setPosition(perdictedPos);

}

void PerdictedGameObject::CacaulatePerdictedPos()
{



	// Using Cubic Splines

	// Will use the last 3 cords recived to work out next one 

	// multiply this by the lag caculated by the server

	//Cubic Bézier curves

	//(1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * P2 + t^3 * P3 ;    0 < t < 1;
	if (timeOfLastUpdate.size() >= PREVOUS_POS_TO_RECORD && prevousVelocity.size() > PREVOUS_POS_TO_RECORD)
	{
		if (timeOfLastUpdate.end()[-1] != 0 && prevousPosition.size() >= PREVOUS_POS_TO_RECORD)
		{

			// Time since last packet info
			float gameTime = (float)NetworkTimeStart::gameTime;


			sf::Vector2f lastPrePath = prevousPosition.end()[-2] - prevousPosition.end()[-3];

			float lastDTime = timeOfLastUpdate.end()[-2] - timeOfLastUpdate.end()[-1];

			float startDTime = timeOfLastUpdate.end()[-1] - timeOfLastUpdate.end()[-3];

			sf::Vector2f lastVelocity = lastPrePath / lastDTime;

			sf::Vector2f startPos = prevousPosition.end()[-3] + startDTime * lastVelocity;

			float currentDTime = gameTime - timeOfLastUpdate.end()[-1];

			sf::Vector2f predicPath = prevousPosition.end()[-1] - prevousPosition.end()[-2];

			float dTime = timeOfLastUpdate.end()[-1] - timeOfLastUpdate.end()[-2];

			sf::Vector2f endpos = prevousPosition.end()[-1] + currentDTime *	predicPath / dTime;

			sf::Vector2f linearConvergence = endpos - startPos;

			float velocity = linearConvergence.y / dTime;

			perdictedPos.y = startPos.y + currentDTime * velocity;

			perdictedPos.x = prevousPosition.end()[-1].x;

		}
	}



}
