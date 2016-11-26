#pragma once
#include "PlayerObject.h"
class GhostPlayer :
	public PlayerObject
{
public:
	GhostPlayer();
	~GhostPlayer();

private:

	/*
	Texture used for pacman sprite
	*/
	sf::Texture ghostTexture;
};

