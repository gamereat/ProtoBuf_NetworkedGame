#include "Ball.h"
#include "GameLogging.h"
#include <random> 
#include "NetworkManager.h" 
Ball::Ball()
{
}

Ball::Ball(sf::Vector2f velocity, sf::Vector2f startPos)
{
	//Set the init values for the ball
	this->velocity = velocity;
 	setPosition(startPos);

	sprite.setPosition(startPos);


}


Ball::~Ball()
{
}

void Ball::Init()
{
	// load ball texture from server 
	if (!ballTexture.loadFromFile("../res/art/ball.png"))
	{
		GameLogging::LogError("Failed to load in paddle texture");
	}
	else
	{

		sprite = sf::Sprite(ballTexture);

		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
		sprite.setPosition(lasteUpdatePosition);

	}
}

void Ball::Update(float deltaTime)
{
	// move the ball based off its velocity
	sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

}



void Ball::Restart()
{
	// Get a new random start pots
	velocity = ChoiceRandomStartingVelocity();
	

	// restart to starting pos 
	sprite.setPosition(ballStartPos);

}



sf::Vector2f Ball::getVelocity()
{
	return velocity;
}

void Ball::setVelocity(sf::Vector2f velocity)
{
	this->velocity = velocity;
}

BallCollionResults Ball::CollisionDetection(Player* players[NUM_PLAYERS])
{

 	// check if ball is out bounds

	//Check if hit the to bottom or top
	// removing 1 so boucnes a wee bit early
	if (sprite.getPosition().y + sprite.getTextureRect().height / 2 > SCREEN_HEIGHT -1  ||
		sprite.getPosition().y - sprite.getTextureRect().height / 2 < 1)
	{
		// flip velocity of ball
		velocity.y *= -1;

		return HitTopBottom;
	}

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (sprite.getPosition().x < players[i]->getPosition().x + players[i]->getSprite().getTextureRect().width&&
			sprite.getPosition().x + sprite.getTextureRect().width> players[i]->getPosition().x &&
			sprite.getPosition().y <players[i]->getPosition().y + players[i]->getSprite().getTextureRect().height  &&
			sprite.getTextureRect().height  + sprite.getPosition().y > players[i]->getPosition().y)
		{
			velocity.x *= -1;
			return BallCollionResults::HitBat;


		}
 
	}
	//Check if either player has scored
	if (sprite.getPosition().x + sprite.getTextureRect().width / 2 > SCREEN_WIDTH )
	{
		return BallCollionResults::PlayerOneScore;
	}
	else if (sprite.getPosition().x - sprite.getTextureRect().width / 2 < 0)
	{
		return BallCollionResults::PlayerTwoScore;

	}
	return BallCollionResults::None;

}

void Ball::SetToStart()
{

	// get a random starting velocity
	velocity = ChoiceRandomStartingVelocity();
}

sf::Vector2f Ball::ChoiceRandomStartingVelocity()
{
	sf::Vector2f randomVelocity;
	// Get a random number for verlociy
	std::default_random_engine generator;
	generator.seed(time(0));
	std::uniform_int_distribution<int> distribution(MIN_STARTING_VELOCITY, MAX_STARTING_VELOCITY);
	randomVelocity.x = distribution(generator);
	randomVelocity.y = distribution(generator);

	// work out direction of ball
	std::uniform_int_distribution<int> direction(0, 1);

	randomVelocity.x *= (direction(generator) == 0) ? -1 : 1;
	randomVelocity.y *=( direction(generator) == 0) ? -1 : 1;
	
	return randomVelocity;
}