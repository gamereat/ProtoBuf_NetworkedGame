#include "PridictedGameObject.h"
#include "StaticMathsLib.h"
#include "NetworkTimeLapse.h"

PridictedGameObject::PridictedGameObject()
{
}


PridictedGameObject::~PridictedGameObject()
{
}
void PridictedGameObject::Init()
{
	perdictedPos = this->lasteUpdatePosition;
}
void PridictedGameObject::CacaulatePerdictedPos()
{


	if (estimateLag != 0 )
	{
		// Using Cubic Splines

		// Will use the last 3 cords recived to work out next one 

		// multiply this by the lag caculated by the server

		//Cubic Bézier curves

		//(1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * P2 + t^3 * P3 ;    0 < t < 1;
		if (timeOfLastUpdate.size() >= PREVOUS_POS_TO_RECORD && prevousVelocity.size() > PREVOUS_POS_TO_RECORD && prevousPosition.size() >= PREVOUS_POS_TO_RECORD)
		{
			if (timeOfLastUpdate.end()[-1] != 0 )
			{



				float time;

				float gameTime = (float)NetworkTimeLapse::gameTime;
				float timeSincePrevousPackage = (gameTime - timeOfLastUpdate.end()[-2])*0.001f;
				float timeSinceLatestPackage = (gameTime - timeOfLastUpdate.end()[-1])*0.001f;


				float timeSinceLastUpdate = (gameTime + estimateLag - timeOfLastUpdate.end()[-1])*0.001f;


				timeSinceLastUpdate = StaticMathsLib::Clamp<float>(0, 1, timeSinceLastUpdate);


				float OneMinusTime = (1 - timeSinceLastUpdate);


				time = StaticMathsLib::Clamp<float>(0, 1, timeSinceLatestPackage);


				sf::Vector2f posLast, posPrev, newPerdictedPos;
				posLast.y = prevousPosition.end()[-2].y + prevousVelocity.end()[-1].y * time;


				sf::Vector2f ipVel;
				ipVel.y = prevousVelocity.end()[-1].y + OneMinusTime * prevousVelocity.end()[-2].y;

				time = StaticMathsLib::Clamp<float>(0, 1, timeSincePrevousPackage);
				posPrev.y = prevousPosition.end()[-1].y + ipVel.y * time;


				newPerdictedPos.x = prevousPosition[0].x;
				newPerdictedPos.y = posLast.y;


				perdictedPos = newPerdictedPos;
			}
		}
 
	}



}
