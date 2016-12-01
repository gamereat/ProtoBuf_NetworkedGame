#include "ServerController.h"
#include "GameLogging.h"


ServerController::ServerController()
{
	playersInGame = 0;
	versionNumber = 2;
	clientNetworkUpdateTime = 1;
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

	
 	int i = 0;
	for each (auto player in players)
	{
		player = new Player(0,  sf::Vector2f(0, 10));
		players[i] = player;
		i++;
	}
	players[0]->setPosition(playerOneStartingLocation);
	players[1]->setPosition(playerTwoStartingLocation);

	ball = new Ball(sf::Vector2f(0, 0), 90, ballStartPos);

 
	return true;
}
void ServerController::Render(sf::RenderWindow* renderWindow)
{
 
	renderWindow->draw(ball->getSprite());
	renderWindow->draw(severVersionNumberText);
}

bool ServerController::Update()
{
	createClientMessage();
	// if there has been more players connected to the network since last frame then send data to them and other players
	// about this new player
	if (playersInGame < networkManger.getPlayersConnected())
	{
		playersInGame++;
		networkManger.SendServerMessage(versionNumber, ball,players, playersInGame);
	}
	// If a player has disconnected 
	else if (playersInGame > networkManger.getPlayersConnected())
	{
		playersInGame--;
		networkManger.SendServerMessage(versionNumber, ball, players, playersInGame);
	}
	//

	// Work out if clients need a update with latest data from server
	float timeSinceClientUpdate = networkUpdateTimer.getElapsedTime().asSeconds();

	// if corrrecnt time has past send update information
	if (timeSinceClientUpdate >= clientNetworkUpdateTime)
	{
		networkUpdateTimer.restart();
		networkManger.SendServerMessage(versionNumber, ball, players, playersInGame);
	}

	networkManger.Update();
	

 	return true;
}

void ServerController::createClientMessage()
{
	std::vector<std::pair<int, ClientMessage::Playerinfromation>> clientsInfo =  std::vector<std::pair<int, ClientMessage::Playerinfromation>>(NUM_PLAYERS);
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		//make sure messages have been recived
		if (networkManger.lastMessageRecivedClients()[i] != nullptr)
		{
			int clientNum = networkManger.lastMessageRecivedClients()[i]->clientnumber();
			ClientMessage::Playerinfromation playerInfo = networkManger.lastMessageRecivedClients()[i]->playerinfo();
		
			clientsInfo[i]  = std::pair<int, ClientMessage::Playerinfromation>(clientNum, playerInfo);

		
		}
		else
		{
			clientsInfo[i] = std::pair<int, ClientMessage::Playerinfromation>(-1, *ClientMessage::Playerinfromation().New());
		}
		
	}

	for (int i = 0; i < clientsInfo.size(); i++)
	{
		if (clientsInfo[i].first != -1)
		{
			players[i]->UpdatePlayer(&(clientsInfo[i].second));
		}
	}

}
