#pragma once
#include "PlayerObject.h"
class PacManPlayer :
	public PlayerObject
{
public:
	PacManPlayer();
	~PacManPlayer();
	 
private:


	/*
	Texture used for pacman sprite
	*/
	sf::Texture pacManTexture;
};

