#pragma once
#include "PlayerObject.h"


/*
Paddle object controlled by player to hit ball around 
*/
class Paddle : public PlayerObject
{
public:
	Paddle();
	~Paddle();

	virtual void Render(sf::RenderWindow* renderWindow);
	virtual void Init();
	virtual void Update(float deltaTime);

private:

	/*
	Texture for the paddle
	*/
	sf::Texture paddleTexture;

};

