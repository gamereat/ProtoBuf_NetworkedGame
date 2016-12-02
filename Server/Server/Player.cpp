#include "Player.h"

#include"GameLogging.h"

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

void Player::UpdatePlayer(ClientMessage::Playerinfromation* playerInfo)
{
	playerNumber = playerInfo->playernumber();

	ClientMessage::playerPos playerpos = playerInfo->pos();
	position = sf::Vector2f(playerpos.posx(), playerpos.posy());
 
	sprite.setPosition(position);
}
