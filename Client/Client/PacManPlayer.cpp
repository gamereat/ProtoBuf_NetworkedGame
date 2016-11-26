#include "PacManPlayer.h"
#include "GameLogging.h"


PacManPlayer::PacManPlayer()
{
	if (!pacManTexture.loadFromFile("../res/art/pacMan.png"))
	{
		GameLogging::LogError("Failed to load in pacman texture");

	}
	else
	{
		sprite = sf::Sprite(pacManTexture);
	}
}


PacManPlayer::~PacManPlayer()
{
}
