#include "NetworkManager.h"
#include "ServerController.h"
#include "GameLogging.h"

NetworkManager::NetworkManager()
{
	portNumber = 7777;

}


NetworkManager::~NetworkManager()
{
}

void NetworkManager::Init()
{
	if(udpSocket.bind(portNumber) != sf::Socket::Done)
	{
		GameLogging::LogError(" Failed to bind udp socket   ");

	}
	udpSocket.setBlocking(false);

}

void NetworkManager::Update()
{
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[24];
	udpSocket.receive(buffer, 24, received, sender, port);

	if (received > 0)
	{
		std::string f = buffer;
		std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
		ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();

		newMessage->ParseFromArray(buffer, sizeof(buffer));
		// Send a debug log of message to logging system when in debug mode 
		GameLogging::Log(newMessage->DebugString());
	}
	
 
}
void NetworkManager::SendServerMessage(int serverVersionNum, Player players[4], Map map, int numConnectedPlayers)
{
	// new server message to be sent to clients
	ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage();
	newMessage->New();
	ServerMessage::ServerInformation* serverInfo = new ServerMessage::ServerInformation();

	serverInfo->set_messagenumber(numOfMessageSend);
	serverInfo->set_serverinformation(serverVersionNum);
	newMessage->set_allocated_serverinfo(serverInfo);

	ServerMessage::Playerinfromation* gamePlayers[NUM_PLAYERS] ;
	for (int player = 0; player < NUM_PLAYERS; player++)
	{
		gamePlayers[player] = new ServerMessage::Playerinfromation();
	}
	// loop for each player
	for (int player = 0; player < NUM_PLAYERS; player++)
	{
		ServerMessage::Playerinfromation* playerInfo = new ServerMessage::Playerinfromation();
		playerInfo->New();
		// Get the pos of the player
		ServerMessage::playerPos* playerPos = new ServerMessage::playerPos();
		playerPos->New();
		sf::Vector2<float> pos = players[player].getPosition();
		playerPos->set_posx(0);
		playerPos->set_posy(0);
	
		playerInfo->set_allocated_pos(playerPos);

		//get other data for the player
		playerInfo->set_playernumber(player);
		playerInfo->set_playerscore(players[player].getScore());
		playerInfo->set_player(players[player].getPlayerType());

		gamePlayers[player] = playerInfo;

	}
	// add player data
	// NOTE: due to wanting to keep a constant message size and restrictions with Proto Buffer 
	// Array could not be used thus Hack to send multiplayers
	newMessage->set_allocated_playerone(gamePlayers[0]);
	newMessage->set_allocated_playertwo(gamePlayers[1]);
	newMessage->set_allocated_playerthree(gamePlayers[2]);
	newMessage->set_allocated_playerfour(gamePlayers[3]);

	ServerMessage::MapData* mapData = new ServerMessage::MapData();

	for (int mapCol = 0; mapCol < MAP_LENGTH; mapCol++)
	{
		ServerMessage::MapData::row* newRow = mapData->add_col();

		for (int mapRow = 0; mapRow < MAP_HIGHT; mapRow++)
		{
			
			// Get tile info from the map 
			newRow->add_tile(map.getMap().at(mapCol).at(mapRow).getTileType());
		}

	}
	
	newMessage->set_allocated_mapinfo(mapData);

	newMessage->set_numofplayer(numConnectedPlayers);

	// increase the number of messaage sent
	numOfMessageSend++; 

	std::vector<std::string> f;
	newMessage->FindInitializationErrors(&f);
	// Make sure message has got all valid feilds
	newMessage->CheckInitialized();

	std::string messageData;
	newMessage->SerializeToString(&messageData);

	SendMessage(messageData);

 }
void NetworkManager::WorkOutSyncTimingForClient()
{
}

void NetworkManager::SendMessage(std::string data)
{
	ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage;
	newMessage->ParseFromString(data);
	// Send a debug log of message to logging system when in debug mode 
	sf::IpAddress recipient = "127.0.0.1";
	unsigned short port = 54000;

	int size = newMessage->ByteSize();
	void *buffer = malloc(size);
	newMessage->SerializeToArray(buffer, size);
	GameLogging::Log("Message Length " + std::to_string(size));


	if (udpSocket.send(buffer,256, recipient, port) != sf::Socket::Done)
	{
		// error...
	}
	else
	{
		ServerMessage::ServerMessage* newMessages = new ServerMessage::ServerMessage();
		newMessages->ParseFromArray(buffer, size);
		GameLogging::Log(newMessages->DebugString());

	}
}
