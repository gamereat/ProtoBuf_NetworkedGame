#include "Ball.h"
#include "GameLogging.h"
#include "NetworkTimeStart.h"
#include "ClientController.h"
Ball::Ball()
{
}

Ball::Ball(sf::Vector2f velocity, sf::Vector2f startPos)
{
	this->velocity = velocity;

	sprite.setPosition(startPos);
}


Ball::~Ball()
{
}

void Ball::Init()
{

	if (!ballTexture.loadFromFile("../res/art/ball.png"))
	{
		GameLogging::LogError("Failed to load in paddle texture");
	}
	else
	{
		sprite = sf::Sprite(ballTexture);

		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);

	}
}

void Ball::Update(float deltaTime)
{

	if (messageData.end()[-1].pos == BALL_START_POS )
	{

		//set pos to new pridect pos 
		sprite.setPosition(BALL_START_POS);
	}
	else
	{
		// work out new perdicted position
		CacaulatePerdictedPos();

		//set pos to new pridect pos 
		sprite.setPosition(perdictedPos);
	}
	// get any update to estiamae lag
//	estimateLag = ;
}

void Ball::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(sprite);

}
 


void Ball::UpdateBallInfo(ServerMessage::BallInformation ballnfo,int messageNum)
{
 
	UpdateMessageInfo(sf::Vector2f(ballnfo.possition().posx(), ballnfo.possition().posy()), sf::Vector2f(ballnfo.velocity().posx(), ballnfo.velocity().posy()), messageNum);

  

}
 
sf::Vector2f Ball::getVelocity()
{
	return velocity;
}


