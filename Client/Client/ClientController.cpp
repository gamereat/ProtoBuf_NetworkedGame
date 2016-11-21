#include "ClientController.h"



ClientController::ClientController()
{
	currentClientGameState = ClientGameState::Init;
}


ClientController::~ClientController()
{
}

bool ClientController::Init()
{
	if (!standardFont.loadFromFile("arial.ttf"))
	{
		GameLogging::LogError("Standard font faile to load");
		return false;
	}

	versionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	versionNumberText.setString("(0.0.1)");

	versionNumberText.setPosition(715,0);
	versionNumberText.setCharacterSize(24);

	versionNumberText.setFillColor(sf::Color::Red);

	return true;
}

bool ClientController::Update()
{
	deltaTime = deltaTimeClock.restart().asMicroseconds();

	switch (currentClientGameState)
	{
	case ClientController::ClientGameState::Init:
		currentClientGameState = ClientGameState::Menu;

		break;
	case ClientController::ClientGameState::Menu:
		currentClientGameState = ClientGameState::ReadyToPlay;

		break;
	case ClientController::ClientGameState::ReadyToPlay:
		currentClientGameState = ClientGameState::Playing;

		break;
	case ClientController::ClientGameState::Playing:
 
		break;
	case ClientController::ClientGameState::GameOver:
		break;
	default:
		break;
	}
	return true;
}

void ClientController::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(versionNumberText);
}
