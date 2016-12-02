#include "Ball.h"
#include "GameLogging.h"


Ball::Ball()
{
}

Ball::Ball(sf::Vector2f velocity, float angle, sf::Vector2f startPos)
{
	this->velocity = velocity;
	this->angle = angle;

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

}

void Ball::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(sprite);

}



float Ball::getAngle()
{
	return angle;
}



void Ball::UpdateBallInfo(ServerMessage::BallInformation ballnfo)
{
	angle = ballnfo.angle();
	velocity = sf::Vector2f( ballnfo.velocity().posx(), ballnfo.velocity().posy());
	sprite.setPosition(sf::Vector2f(ballnfo.possition().posx(), ballnfo.possition().posy()));
}

sf::Vector2f Ball::getVelocity()
{
	return velocity;
}

