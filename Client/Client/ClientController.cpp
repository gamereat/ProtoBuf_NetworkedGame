#include "ClientController.h"


ClientController::ClientController()
{
	currentClientGameState = ClientGameState::Menu;
	
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		paddle[i] = new Paddle();
	}

	ball = new Ball();

	serverNetworkUpdateTime = 0.2;
 
}


ClientController::~ClientController()
{

 	// clean up memory

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		if (paddle[i])
		{
			delete paddle[i];
			paddle[i] = nullptr;
		}
 	}
	
	if (ball)
	{
		delete ball;
		ball = nullptr;
	}
}

bool ClientController::Init()
{
	// init the fonts 
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
	

	// Init the players
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		paddle[i]->Init();
	}

	
	paddle[0]->setPlayerControls(false);
	paddle[1]->setPlayerControls(true);

	// init the network
	networkManager.Init();



	ball->Init();


	lastSeverMessageRecived = 0;

	menu = new Menu();
	menu->Init(window);

	return true;
}

bool ClientController::Update()
{
	deltaTime = deltaTimeClock.restart().asSeconds();
	
	
	
	switch (currentClientGameState)
	{
		case ClientController::ClientGameState::Init:
		{
			currentClientGameState = ClientGameState::Menu;
			break;
		}
		case ClientController::ClientGameState::Menu:
		{
			if (menu->Update())
			{
				currentClientGameState = ClientGameState::ReadyToPlay;

			}

			break;
		}
		case ClientController::ClientGameState::ReadyToPlay:
		{	
			connectToGameSever();
		}
		case ClientController::ClientGameState::Playing:
		{
			currentClientGameState = ClientGameState::Playing;
			UpdateGameFromServer();

			// Work out if clients need a update with latest data from server
			float timeSinceClientUpdate = networkUpdateTimer.getElapsedTime().asSeconds();

			// if corrrecnt time has past send update information
			if (timeSinceClientUpdate >= serverNetworkUpdateTime)
			{
				networkUpdateTimer.restart();
				UpdateGameToServer();
			}

			networkManager.Update();

			// Init the players
			for (int i = 0; i < NUM_PLAYERS; i++)
			{
				paddle[i]->Update(deltaTime);
			}

			ball->Update(deltaTime);


			break;
			break;
		}
		case ClientController::ClientGameState::GameOver:
		{	break;
		}
	}


	return true;
}

void ClientController::Render(sf::RenderWindow* renderWindow)
{
	switch (currentClientGameState)
	{
		case ClientController::ClientGameState::Init:
		{
 			break;
		}
		case ClientController::ClientGameState::Menu:
		{
			menu->Render(renderWindow);

			break;
		}
		case ClientController::ClientGameState::ReadyToPlay:
		{
 
			break;
		}
		case ClientController::ClientGameState::Playing:
		{
			// Render Players
			for (int i = 0; i < NUM_PLAYERS; i++)
			{
				paddle[i]->Render(renderWindow);

			}

			ball->Render(renderWindow);
			renderWindow->draw(clientVersionNumberText);
			renderWindow->draw(clientNumberText);

			break;
		}
		case ClientController::ClientGameState::GameOver:
		{	
			break;
		}
	
	}
 
}

void ClientController::Disconect()
{
	networkManager.SendDissconectMessage();

}

void ClientController::setWindow(sf::Window * window)
{
	this->window = window;
}

void ClientController::connectToGameSever()
{

	// Connect to server
	networkManager.SentConnectionMessage(clientVersionNumber);
	// once Connected get player info

	while (networkManager.getLastServerMessage() == nullptr)
	{
		networkManager.Update();

	};
	ServerMessage::ServerMessage serverMessage = *networkManager.getLastServerMessage();


	ServerMessage::Playerinfromation updatePlayers[2];
	updatePlayers[0] = serverMessage.playerone();
	updatePlayers[1] = serverMessage.playertwo();
	UpdatePlayers(updatePlayers);


	UpdateBall(serverMessage.ballinformation());

	// get the player number
	int playerNum = serverMessage.playernumber();
	int playerConncted = serverMessage.playersconnected();

	// Player number relates to which player the user is controlling 

	switch (playerNum)
	{
	case 0:
		break;
	case 1: 

		break;
	}
	
	controllingPlayer = paddle[playerNum];

	// set the player number of the controlling player
	controllingPlayer->setPlayerNumber(playerNum);

	clientNumberText.setFont(standardFont);

	// Adding 1 to player num to make it more readable to the user
	// ie if only 1 user is conenct it is 1/1 rather than 0/1 which is correct but not understadable
	clientNumberText.setPosition(600, 25);
	clientNumberText.setCharacterSize(24);

	clientNumberText.setFillColor(sf::Color::Red);

	controllingPlayer->setIsControllable(true);
	// Update the game to display this info
	UpdateGameFromServer();


}

ClientMessage::Playerinfromation* ClientController::GetPlayerInfo()
{
	sf::Vector2f pos = controllingPlayer->getPosition();

	int playerNum = controllingPlayer->getPlayerNumber();


	ClientMessage::playerPos* playerPos = new ClientMessage::playerPos();


	playerPos->set_posx(pos.x);
	playerPos->set_posy(pos.y);

	ClientMessage::Playerinfromation* playerInfo = new ClientMessage::Playerinfromation();

	playerInfo->set_playernumber(playerNum);


	playerInfo->set_allocated_pos(playerPos);
	
	std::vector<std::string >t;
	playerInfo->FindInitializationErrors(&t);
 
	return playerInfo;
}

void ClientController::UpdateGameToServer()
{

	networkManager.SentMessageToServer(clientVersionNumber, GetPlayerInfo(), ClientMessage::ClientMessage_AdditioanlRequests_None);
}

void ClientController::UpdateGameFromServer()
{
	 ServerMessage::ServerMessage* newMessage = networkManager.getLastServerMessage();

	 // Check if any messages have been recived yet
	 if (newMessage != nullptr)
	 {
		 ServerMessage::ServerInformation serverInfo = newMessage->serverinfo();
		 unsigned int  messageNumber =  serverInfo.messagenumber();


 			 // Update the map with information from the server

			 //collect player information

			 ServerMessage::Playerinfromation updatePlayers[2];
			 updatePlayers[0] = newMessage->playerone();
			 updatePlayers[1] = newMessage->playertwo();


			 // Update players
			 UpdatePlayers(updatePlayers);
			 int playerNum = newMessage->playernumber();
			 int playerConncted = newMessage->playersconnected();

			// clientNumberText.setString("Client Number " + std::to_string(playerNum + 1) + "/" + std::to_string(playerConncted));

			 // Update ball location
			 UpdateBall(newMessage->ballinformation());
	 }
}


void ClientController::UpdatePlayers(ServerMessage::Playerinfromation players[NUM_PLAYERS])
{
	if (controllingPlayer != paddle[0])
	{
		paddle[0]->UpdatePlayerInfo(players[0]);
	}
	if (controllingPlayer != paddle[1])
	{
		paddle[1]->UpdatePlayerInfo(players[1]);
	}

 }

void ClientController::UpdateBall(ServerMessage::BallInformation ballInfo)
{
	ball->UpdateBallInfo(ballInfo);
}
