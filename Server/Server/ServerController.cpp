#include "ServerController.h"
#include "GameLogging.h"


ServerController::ServerController()
{
	playersInGame = 0;
	versionNumber = 2;
	gameMap = new Map();

}


ServerController::~ServerController()
{
}

bool ServerController::Init()
{
	if (!standardFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
	//	return false;
	}

	severVersionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	severVersionNumberText.setString("Server: (0.0.2)");

	severVersionNumberText.setPosition(715, 0);
	severVersionNumberText.setCharacterSize(24);

	severVersionNumberText.setFillColor(sf::Color::Red);
	networkManger.Init();

	
	Map* map;
	int i = 0;
	for each (auto player in players)
	{
		player = new Player(0, ServerMessage::Playerinfromation::PlayerType::Playerinfromation_PlayerType_Ghost, sf::Vector2f(0, 10));
		players[i] = player;
		i++;
	}
//	networkManger.SendServerMessage(2, *players, *map, 1);
	 
 
	return true;
}
void ServerController::Render(sf::RenderWindow* renderWindow)
{
 
	renderWindow->draw(severVersionNumberText);
}

bool ServerController::Update()
{
	// if there has been more players connected to the network since last frame then send data to them and other players
	// about this new player
	if (playersInGame < networkManger.getPlayersConnected())
	{
		playersInGame++;
	}
	// If a player has disconnected 
	else if (playersInGame > networkManger.getPlayersConnected())
	{
		playersInGame--;
	}
	networkManger.SendServerMessage(versionNumber, *players, *gameMap, playersInGame);

	networkManger.Update();
	
	return true;
}