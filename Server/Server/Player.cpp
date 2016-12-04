#include "Player.h"

#include"GameLogging.h"
#include "NetworkTimeLapse.h"
#include "ServerController.h"
Player::Player()
{
}

Player::Player(int score, sf::Vector2f pos) 
{
 	currentScore = score;
}

Player::~Player()
{
}


void Player::Init() 
{

 	if (!paddleTexture.loadFromFile("../res/art/paddle.png"))
	{
		GameLogging::LogError("Failed to load in paddle texture");
	}
	else
	{
		sprite = sf::Sprite(paddleTexture);

		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	}


	perdictedPos = this->lasteUpdatePosition;

}

void Player::Update(float deltaTime)
{
	CacaulatePerdictedPos();
	sprite.setPosition(perdictedPos);
	estimateLag = NetworkTimeLapse::GetClientEsimateLag(playerNumber);

	
}

void Player::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(sprite);

}
void Player::CacaulatePerdictedPos()
{
 

	if (estimateLag != 0)
	{
		// Using Cubic Splines

		// Will use the last 3 cords recived to work out next one 

		// multiply this by the lag caculated by the server

		//Cubic Bézier curves

		//(1-t)^3 * P0 + 3 * (1-t)^2 * t * P1 + 3 * (1-t) * t^2 * P2 + t^3 * P3 ;    0 < t < 1;
		if (timeOfLastUpdate.size() >= PREVOUS_POS_TO_RECORD && prevousVelocity.size() > 2)
		{
			if (timeOfLastUpdate.end()[-1] != 0 && prevousPosition.size() >= 2)
			{



				float time;
				// Time since last packet info
				float gameTime = (float)NetworkTimeLapse::gameTime;
				float tSincePrevPacket = (gameTime - timeOfLastUpdate.end()[-2])*0.001f;
				float tSinceLastPacket = (gameTime - timeOfLastUpdate.end()[-1])*0.001f;
				
				
				float tSinceLastUpdate = (gameTime + estimateLag - gameTimeAtLastUpdate)*0.001f;

 
				tSinceLastUpdate = clamp(0, 1, tSinceLastUpdate);
 

				float OneMinusTime = (1 - tSinceLastUpdate);
 
	 
				//
				// Linear interpolation - should be perfect for static linear velocity tests with 1 server and 1 client
				// More clients will mean the clock varies a bit from clients -> srv -> other clients
				//
				time = clamp(0,1,tSinceLastPacket);

				// Calculate current position based on packet info
				 sf::Vector2f posLast, posPrev , newPerdictedPos;
 				posLast.y = prevousPosition.end()[-2].y + prevousVelocity.end()[-1].y * time;
 
				// Calculate predicted previous position - use time since last interpolation time
				// Calculate interpolated velocity for a bit more smoothness
				sf::Vector2f ipVel;
 				ipVel.y =  prevousVelocity.end()[-1].y + OneMinusTime * prevousVelocity.end()[-2].y;
 
				time = clamp(0, 1, tSincePrevPacket);
 				posPrev.y = prevousPosition.end()[-1].y + ipVel.y * time;
 
				// Calculate position, interpolating from posPrev -> posLast as time goes by
				// to correct towards the last received packet
				newPerdictedPos.x = prevousPosition[0].x;
				newPerdictedPos.y = posLast.y ;
 

				perdictedPos = newPerdictedPos;
			}
		}
	}



}

void Player::setScore(int newScore)
{
	currentScore = newScore;
}

int Player::getScore()
{
	return currentScore;
}

void Player::UpdatePlayer(ClientMessage::Playerinfromation* playerInfo)
{
	playerNumber = playerInfo->playernumber();

	ClientMessage::playerPos playerpos = playerInfo->pos();
	lasteUpdatePosition = sf::Vector2f(playerpos.posx(), playerpos.posy());


	gameTimeAtLastUpdate = NetworkTimeLapse::gameTime;
	prevousPosition.push_back(lasteUpdatePosition);
 
	prevousMessageTimes.push_back(NetworkTimeLapse::gameTime);
	sf::Vector2f velocity;
	sf::Vector2f distance;
 

	if (prevousPosition.size() > 2)
	{
		distance.x = prevousPosition.end()[-1].x - prevousPosition.end()[-2].x;
		distance.y = prevousPosition.end()[-1].y - prevousPosition.end()[-2].y;

		float tDistance = sqrt(distance.x * distance.x + distance.y * distance.y);

		if (tDistance == 0)
		{

			prevousVelocity.push_back(sf::Vector2f(0, 0));
		}
		else
		{
			sf::Vector2f unitVelocity = sf::Vector2f((distance.x / tDistance), (distance.y / tDistance));

			velocity.x = 0;
			velocity.y = unitVelocity.y * PADDLE_SPEED;

			prevousVelocity.push_back(velocity);
		}
	}
	timeOfLastUpdate.push_back(gameTimeAtLastUpdate);
 }

float Player::clamp(float lower, float upper, float num)
{
	return num <= lower ? lower : num >= upper ? upper : num;
}

