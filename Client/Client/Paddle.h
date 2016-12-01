#pragma once
#include "PlayerObject.h"

class Paddle : public PlayerObject
{
public:
	Paddle();
	~Paddle();

	virtual void Render(sf::RenderWindow* renderWindow);
	virtual void Init();
	virtual void Update(float deltaTime);

private:

	sf::Texture paddleTexture;

};

