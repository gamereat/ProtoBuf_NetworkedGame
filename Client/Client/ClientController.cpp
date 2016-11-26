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
	if (!standardFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
		return false;
	}

	clientVersionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	clientVersionNumberText.setString("(0.0.1)");

	clientVersionNumberText.setPosition(715,0);
	clientVersionNumberText.setCharacterSize(24);

	clientVersionNumberText.setFillColor(sf::Color::Red);

	networkManager.Init();

	ClientMessage::ClientInformation* client = new ClientMessage::ClientInformation();
	ClientMessage::Playerinfromation* player = new ClientMessage::Playerinfromation();
	ClientMessage::playerPos* pos = new ClientMessage::playerPos();
	pos->set_posx(0);
	pos->set_posy(0);
	player->set_playernumber(0);
	player->set_type(ClientMessage::Playerinfromation_PlayerType_Ghost);
	player->set_allocated_pos(pos); 
	


	networkManager.SentMessageToServer(1, player);
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

	networkManager.Update();
	return true;
}

void ClientController::Render(sf::RenderWindow* renderWindow)
{
	renderWindow->draw(clientVersionNumberText);
}
