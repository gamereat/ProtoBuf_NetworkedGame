#include "ServerController.h"
#include "GameLogging.h"


ServerController::ServerController()
{
}


ServerController::~ServerController()
{
}

bool ServerController::Init()
{
	if (!standardFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
		return false;
	}

	severVersionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	severVersionNumberText.setString("Server: (0.0.1)");

	severVersionNumberText.setPosition(715, 0);
	severVersionNumberText.setCharacterSize(24);

	severVersionNumberText.setFillColor(sf::Color::Red);

	return true;
}

bool ServerController::Update()
{
	return false;
}