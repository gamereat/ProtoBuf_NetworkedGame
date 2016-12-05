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

	messageData =  std::vector<playerInfo>(3);
}

void Player::Update(float deltaTime)
{

	perdictedPos = lasteUpdatePosition;

	CacaulatePerdictedPos();
	sprite.setPosition(perdictedPos);
	estimateLag = NetworkTimeLapse::GetClientEsimateLag(playerNumber);
 //	lasteUpdatePosition = messageData.end()[-1].pos;
	
}

void Player::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(sprite);

}
void Player::CacaulatePerdictedPos()
{
 

	if (messageData.size() == 3)
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
			float gameTime = (float)NetworkTimeLapse::gameTime - estimateLag;


			sf::Vector2f lastPrePath = messageData.end()[-2].pos - messageData.end()[-3].pos;

			float lastDTime = messageData.end()[-2].timeOfUpdat- messageData.end()[-3].timeOfUpdat;

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

void Player::setScore(int newScore)
{
	currentScore = newScore;
}

int Player::getScore()
{
	return currentScore;
}

void Player::UpdatePlayer(ClientMessage::Playerinfromation * playeData, int messageNumber)
{
	if (messageData.size() > 0)
	{
		// got a old messsage
		if (messageData.end()[-1].messageNumber >= messageNumber)
		{
			return;
		}
		playerNumber = playeData->playernumber();

		playerInfo info;

		info.messageNumber = messageNumber;


		ClientMessage::playerPos playerpos = playeData->pos();
		lasteUpdatePosition = sf::Vector2f(playerpos.posx(), playerpos.posy());


		info.pos = lasteUpdatePosition;




		gameTimeAtLastUpdate = NetworkTimeLapse::gameTime - estimateLag;

		info.timeOfUpdat = NetworkTimeLapse::gameTime - estimateLag;

		sf::Vector2f velocity;
		sf::Vector2f distance;


			distance.x = messageData.end()[-1].pos.x - messageData.end()[-1].pos.x;
			distance.y = messageData.end()[-1].pos.y - messageData.end()[-1].pos.y;

			float tDistance = sqrt(distance.x * distance.x + distance.y * distance.y);

			if (tDistance == 0)
			{

				info.velocity = sf::Vector2f(0, 0);
			}
			else
			{
				sf::Vector2f unitVelocity = sf::Vector2f((distance.x / tDistance), (distance.y / tDistance));

				velocity.x = 0;
				velocity.y = unitVelocity.y * PADDLE_SPEED;

				info.velocity = velocity;
			}
	

		 



			messageData.push_back(info);
		//timeOfLastUpdate.push_back(gameTimeAtLastUpdate);
	}
 }

 
