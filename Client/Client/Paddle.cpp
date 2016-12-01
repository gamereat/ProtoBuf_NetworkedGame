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
	
	
	if (!paddleTexture.loadFromFile("../res/art/ghost.png"))
	{
		GameLogging::LogError("Failed to load in paddle texture");
	}
	else
	{
		sprite = sf::Sprite(paddleTexture);
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



