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

}

void Player::Update(float deltaTime)
{

	perdictedPos = lasteUpdatePosition;

	//CacaulatePerdictedPos();
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
		if (timeOfLastUpdate.size() >= PREVOUS_POS_TO_RECORD && prevousVelocity.size() > PREVOUS_POS_TO_RECORD)
		{
			if (timeOfLastUpdate.end()[-1] != 0 && prevousPosition.size() >= PREVOUS_POS_TO_RECORD)
			{
 
				// Time since last packet info
				float gameTime = (float)NetworkTimeLapse::gameTime;
 

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

 
