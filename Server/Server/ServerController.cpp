#include "ServerController.h"
#include "GameLogging.h"
#include "NetworkManager.h"
#include "Player.h"
#include "Ball.h"
#include "AIPlayer.h"

ServerController::ServerController()
{
	playersInGame = 0;
	versionNumber = 2;
	clientNetworkUpdateTime = 0.03;
}


ServerController::~ServerController()
{

	// clean memory up
	if (networkManger)
	{
		delete networkManger;
		networkManger = nullptr;
	}

	if (ball)
	{
		delete ball;
		ball = nullptr;
	}

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		delete players[i]; 
		players[i] = nullptr;
	}
}

bool ServerController::Init()
{
	// get a new network manager 
	networkManger = new NetworkManager();
	networkManger->Init();


	if (!standardFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
		return false;
	}

	severVersionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	severVersionNumberText.setString("Server: (0.0.2)");

	severVersionNumberText.setPosition(SCREEN_WIDTH  - severVersionNumberText.getString().getSize() * severVersionNumberText.getCharacterSize(), 0);
	severVersionNumberText.setCharacterSize(24);
	;
	severVersionNumberText.setFillColor(sf::Color::Red);


 
	// Create user controlled player
	players[0] =  new Player(0,  sf::Vector2f(0, 10));
	players[0]->Init(); 
	players[0]->setPosition(playerOneStartingLocation);
	players[0]->Init();

	// Create second player player
	players[1] = new Player(0, sf::Vector2f(0, 10));
//	players[1] = aiPlayer;
	players[1]->Init();
	players[1]->setPosition(playerTwoStartingLocation);
	players[1]->Init();

	// load in ball
 	ball = new Ball(sf::Vector2f(0, 0),  ballStartPos);
	ball->Init();
	//aiPlayer->setBall(ball);

	gameStarted = false;
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
}

bool ServerController::Update()
{
	// get new delta time 
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


	if (playersInGame == 2 && !gameStarted)
	{
		ball->SetToStart();
		gameStarted = true;
	}

	// get any collision with ball
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
		ball->Restart();

		break;

	case PlayerTwoScore:
		players[1]->setScore(players[1]->getScore() + 1);
		ball->Restart();
	default:
		break;
	}


 

	for (int i = 0; i < NUM_PLAYERS; i ++ )
	{
		players[i]->Update(deltaTime);
		
		if (networkManger->hasRecivedClientInfo(i) == true)
		{
			createClientMessage();
			networkManger->setHasRecivedClientInfo(i, false);
		}
	}
	return true;
}

void ServerController::createClientMessage()
{
	// get a new client message
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
			players[i]->UpdatePlayer(&(clientsInfo[i].second), networkManger->lastMessageRecivedClients()[i]->clientinfo().messagenumber());
		}
	}



}
