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
	perdictedPos = lasteUpdatePosition;

}

void Player::Update(float deltaTime)
{


	CacaulatePerdictedPos();
	sprite.setPosition(perdictedPos);
	estimateLag = NetworkTimeLapse::GetClientEsimateLag(playerNumber);
 //	lasteUpdatePosition = messageData.end()[-1].pos;
	
}

void Player::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(sprite);

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

		ClientMessage::playerPos playerpos = playeData->pos();
		lasteUpdatePosition = sf::Vector2f(playerpos.posx(), playerpos.posy());

		UpdateMessageInfo(sf::Vector2f(playerpos.posx(), playerpos.posy()), NetworkTimeLapse::gameTime, messageNumber);
	 
		playerNumber = playeData->playernumber();
 


	}
 }

 
