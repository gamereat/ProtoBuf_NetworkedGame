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
	NetworkTimeStart networkTimer;

	estimateLag = 5;
	if (estimateLag != 0)
	{
		// Using Cubic Splines

		// Will use the last 3 cords recived to work out next one 

		// multiply this by the lag caculated by the server

		//Cubic Bézier curves

		//(1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * P2 + t^3 * P3 ;    0 < t < 1;

		if (timeOfLastUpdate != 0 && prevousPosition.size() >= PREVOUS_POS_TO_RECORD)
		{
			sf::Vector2f newPerdictedPos;

			int time = (networkTimer.getTimeSinceEpoch() - timeOfLastUpdate) / estimateLag;

			int OneMinusTime = (1 - time);


			newPerdictedPos.x = powf(OneMinusTime, 3) * prevousPosition[3].x;
			newPerdictedPos.x += 3 * powf(OneMinusTime, 2) * time * prevousPosition[2].x;
			newPerdictedPos.x += 3 * OneMinusTime * powf(time, 2) * prevousPosition[1].x;
			newPerdictedPos.x += powf(time, 3) * prevousPosition[0].x;

			newPerdictedPos.y = powf(OneMinusTime, 3) * prevousPosition[3].y;
			newPerdictedPos.y += 3 * powf(OneMinusTime, 2) * time * prevousPosition[2].y;
			newPerdictedPos.y += 3 * OneMinusTime * powf(time, 2) * prevousPosition[1].y;
			newPerdictedPos.y += powf(time, 3) * prevousPosition[0].y;


			perdictedPos = newPerdictedPos;
		}

	}



}
