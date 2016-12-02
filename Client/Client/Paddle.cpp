#include "Paddle.h"
#include "GameLogging.h"


Paddle::Paddle()
{
}


Paddle::~Paddle()
{
}
void Paddle::Init()
{

	// Calling super class init function 
	PlayerObject::Init();
	
	
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

void Paddle::Update(float deltaTime)
{

	// Calling super class update function 
	PlayerObject::Update(deltaTime);
}
void Paddle::Render(sf::RenderWindow * renderWindow)
{
	// Calling super class render function 
	PlayerObject::Render(renderWindow);
}



