#include "ClientController.h"


ClientController::ClientController()
{
	currentClientGameState = ClientGameState::Init;

	pacManPlayer = new PacManPlayer();

	for (int i = 0; i < 4; i++)
	{
		ghosts[i] = new GhostPlayer();
	}
}


ClientController::~ClientController()
{
	// Free up memory

	if (pacManPlayer)
	{
		delete pacManPlayer;
		pacManPlayer = nullptr;
	}


	for (int i = 0; i < 4; i++)
	{
		if (ghosts[i])
		{
			delete ghosts[i];
			ghosts[i] = nullptr;
		}

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
	

	// init the network
	networkManager.Init();

	map.Init();

	pacManPlayer->Init();
	pacManPlayer->setIsControllable(true);
	for (int i = 0; i < 4; i++)
	{
		ghosts[i]->Init();
	}

	return true;
}

bool ClientController::Update()
{
	deltaTime = deltaTimeClock.restart().asSeconds();
	
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
	pacManPlayer->Update(deltaTime);

	for (int i = 0; i < 4; i++)
	{
		ghosts[i]->Update(deltaTime);
	}

	networkManager.Update();
	UpdateGameFromServer();

	return true;
}

void ClientController::Render(sf::RenderWindow* renderWindow)
{
	//map.Render(renderWindow);
	pacManPlayer->Render(renderWindow);
	for (int i = 0; i < 4; i++)
	{
		ghosts[i]->Render(renderWindow);
	}
	renderWindow->draw(clientVersionNumberText);
}

ClientMessage::Playerinfromation ClientController::GetPlayerInfo()
{
	sf::Vector2f pos = controllingPlayer->getPosition();

	ClientMessage::Playerinfromation_PlayerType type = controllingPlayer->getPlayerType();

	int playerNum = controllingPlayer->getPlayerNumber();


	ClientMessage::playerPos playerPos;

	playerPos.set_posx(pos.x);
	playerPos.set_posy(pos.y);

	ClientMessage::Playerinfromation playerInfo;

	playerInfo.set_type(type);
	playerInfo.set_playernumber(playerNum);


	playerInfo.set_allocated_pos(&playerPos);

	return playerInfo;
}

void ClientController::UpdateGameToServer()
{

	networkManager.SentMessageToServer(clientVersionNumber, &GetPlayerInfo());
}

void ClientController::UpdateGameFromServer()
{
	 ServerMessage::ServerMessage newMessage = networkManager.getLastServerMessage();

	 ServerMessage::ServerInformation serverInfo =   newMessage.serverinfo();

	 unsigned int  messageNumber = serverInfo.messagenumber();
	 // Check if a new message has been recived
	 if (messageNumber> lastSeverMessageRecived)
	 {
		 // Check if a message has been lost 
		 if (lastSeverMessageRecived++ != messageNumber)
		 {
			 //ERROR: 
			 GameLogging::LogError("Message has been lost");
			
			 //TODO: use some interpulation to work fix errors from missing messages 
		 }

		 // Update the map with information from the server
		 UpdateMap(newMessage.mapinfo());

		 //collect player information

		 ServerMessage::Playerinfromation updatePlayers[4];
		 updatePlayers[0] = newMessage.playerone();
		 updatePlayers[1] = newMessage.playertwo();
		 updatePlayers[2] = newMessage.playerthree();
		 updatePlayers[3] = newMessage.playerfour();

		 // Update players
		 UpdatePlayers(updatePlayers);

	 }
}

void ClientController::UpdateMap(ServerMessage::MapData mapData)
{
	// Map the map data to the map objects
	std::vector<std::vector<MapObject>> newMap;

	// loop for the height 
	for (int i = 0; i < MAP_LENGTH ; i++)
	{
		std::vector <MapObject> col;

		// loop for width
		for (int j = 0;j< MAP_HIGHT; j++)
		{
			// Set the tile based off the server info
			MapObject obj;
			obj.setTileType(mapData.col(i).tile(j));
			col.push_back(obj);

		}
		newMap.push_back(col);
	}
	map.updateMap(newMap);
}

void ClientController::UpdatePlayers(ServerMessage::Playerinfromation players[4])
{
}
