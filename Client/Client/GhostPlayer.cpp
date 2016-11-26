#include "GhostPlayer.h"
#include "GameLogging.h"


GhostPlayer::GhostPlayer()
{
	if (!ghostTexture.loadFromFile("../res/art/ghost.png"))
	{
		GameLogging::LogError("Failed to load in pacman texture");

	}
	else
	{
		sprite = sf::Sprite(ghostTexture);
	}
}


GhostPlayer::~GhostPlayer()
{
}
