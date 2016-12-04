#include "ServerController.h"
#include "GameLogging.h"
#include "NetworkManager.h"
#include "Player.h"
#include "Ball.h"

ServerController::ServerController()
{
	playersInGame = 0;
	versionNumber = 2;
	clientNetworkUpdateTime = 0.01;
}


ServerController::~ServerController()
{
	if (networkManger)
	{
		delete networkManger;
		networkManger = nullptr;
	}
}

bool ServerController::Init()
{
	networkManger = new NetworkManager();
	if (!standardFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
	//	return false;
	}

	severVersionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	severVersionNumberText.setString("Server: (0.0.2)");

	severVersionNumberText.setPosition(650, 0);
	severVersionNumberText.setCharacterSize(24);

	severVersionNumberText.setFillColor(sf::Color::Red);
	networkManger->Init();


	playerOneScore.setFont(standardFont);
 
	playerOneScore.setString("0");

	playerOneScore.setPosition(50, SCREEN_HEIGHT - 50);
	playerOneScore.setCharacterSize(24);

	playerTwoScore.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	playerTwoScore.setString("0");

	playerTwoScore.setPosition(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50);
	playerTwoScore.setCharacterSize(24);

  
	int i = 0;
	for each (auto player in players)
	{
		player = new Player(0,  sf::Vector2f(0, 10));
		players[i] = player;
		i++;
		player->Init();
	}
	players[0]->setPosition(playerOneStartingLocation);
	players[1]->setPosition(playerTwoStartingLocation);

	players[0]->Init();
	players[1]->Init();
	ball = new Ball(sf::Vector2f(10, 0), 90, ballStartPos);
	ball->Init();
 
	return true;
}
void ServerController::Render(sf::RenderWindow* renderWindow)
{
	for each (auto player in players)
	{ 
		player->Render(renderWindow);
	}
	renderWindow->draw(ball->getSprite());
	renderWindow->draw(severVersionNumberText);
	renderWindow->draw(playerOneScore);
	renderWindow->draw(playerTwoScore);
}

bool ServerController::Update()
{
	deltaTime = deltaTimeClock.restart().asSeconds();


	// if there has been more players connected to the network since last frame then send data to them and other players
	// about this new player
	if (playersInGame < networkManger->getPlayersConnected())
	{
 
		playersInGame++;
		networkManger->SendServerMessage(versionNumber, ball,players, playersInGame);
	}
	// If a player has disconnected 
	else if (playersInGame > networkManger->getPlayersConnected())
	{
 
		playersInGame--;
		networkManger->SendServerMessage(versionNumber, ball, players, playersInGame);
	}
	//

	// Work out if clients need a update with latest data from server
	float timeSinceClientUpdate = networkUpdateTimer.getElapsedTime().asSeconds();

	// if corrrecnt time has past send update information
	if (timeSinceClientUpdate >= clientNetworkUpdateTime)
	{
 
		networkUpdateTimer.restart();
		networkManger->SendServerMessage(versionNumber, ball, players, playersInGame);
	}

	networkManger->Update();
	
	ball->Update(deltaTime);

	switch (ball->CollisionDetection(players))
	{

	case None:
		break;

	case HitBat:
		break;

	case HitTopBottom:
		break;

	case PlayerOneScore:
		players[0]->setScore(players[0]->getScore() + 1);
		playerOneScore.setString(std::to_string(players[0]->getScore()));

		ball->Restart();

		break;

	case PlayerTwoScore:
		players[1]->setScore(players[1]->getScore() + 1);
		playerTwoScore.setString(std::to_string(players[1]->getScore()));
		ball->Restart();
	default:
		break;
	}


 

	for (int i = 0; i < NUM_PLAYERS; i ++ )
	{
		players[i]->Update(deltaTime);
		
		if (networkManger->recivedClientInfo[i] == true)
		{
			createClientMessage();
			networkManger->recivedClientInfo[i] = false;
		}
	}
	return true;
}

void ServerController::createClientMessage()
{
	std::vector<std::pair<int, ClientMessage::Playerinfromation>> clientsInfo =  std::vector<std::pair<int, ClientMessage::Playerinfromation>>(NUM_PLAYERS);
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		//make sure messages have been recived
		if (networkManger->lastMessageRecivedClients()[i] != nullptr)
		{
			int clientNum = networkManger->lastMessageRecivedClients()[i]->clientnumber();
			ClientMessage::Playerinfromation playerInfo = networkManger->lastMessageRecivedClients()[i]->playerinfo();
		
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
