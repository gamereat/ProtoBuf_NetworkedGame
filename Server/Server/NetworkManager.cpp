#include "NetworkManager.h"
#include "ServerController.h"
#include "GameLogging.h"
#include "Ball.h"
#include "Player.h"


NetworkManager::NetworkManager()
{
	// set the deafult port
	portNumber = SERVER_PORT;

	// set the number of players connected to 0
	playerConnected = 0;
	
	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		numOfMessageSend.push_back(0);
		lastServerMessage.push_back(nullptr);
	}

	networkTimeLapse = new NetworkTimeLapse();


	recivedClientInfo = std::vector<bool>(NUM_PLAYERS);

}


NetworkManager::~NetworkManager()
{
	if (networkTimeLapse)
	{
		delete networkTimeLapse;
		networkTimeLapse = nullptr;
	}
}

void NetworkManager::Init()
{
	networkTimeLapse->Init();
	if(udpSocket.bind(portNumber) != sf::Socket::Done)
	{
		GameLogging::LogError(" Failed to bind udp socket   ");

	}
	udpSocket.setBlocking(false);

	recivedClientInfo = std::vector<bool>(NUM_PLAYERS);
}

void NetworkManager::Update()
{
	networkTimeLapse->Update();
	ReciveClientInfo();
 
}
void NetworkManager::SendServerMessage(int serverVersionNum, Ball* ball,Player* playerData[NUM_PLAYERS], int numConnectedPlayers)
{
	for (int client = 0; client < numConnectedPlayers; client++)
	{

		// new server message to be sent to clients
		ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage();
		newMessage->New();

		// Get additional information for player
		ServerMessage::AdditionalInformation* additionalInfo = new ServerMessage::AdditionalInformation();
 

		ServerMessage::BallInformation* ballInfo = new ServerMessage::BallInformation();

		ServerMessage::Vector2f* ballPos = new ServerMessage::Vector2f();
		ServerMessage::Vector2f* ballVelocity = new ServerMessage::Vector2f();

		ballPos->set_posx(ball->getPosition().x);
		ballPos->set_posy(ball->getPosition().y);

		ballVelocity->set_posx(ball->getVelocity().x);
		ballVelocity->set_posy(ball->getVelocity().y);

		ballInfo->set_angle(0);
		ballInfo->set_allocated_possition(ballPos);
		ballInfo->set_allocated_velocity(ballVelocity);

		newMessage->set_allocated_ballinformation(ballInfo);



		//Get player infromation
		ServerMessage::Playerinfromation* gamePlayers[NUM_PLAYERS];
		for (int player = 0; player < NUM_PLAYERS; player++)
		{
			gamePlayers[player] = new ServerMessage::Playerinfromation();
		}

		// loop for each player
		for (int player = 0; player < NUM_PLAYERS; player++)
		{
			ServerMessage::Playerinfromation* playerInfo = gamePlayers[player];
			playerInfo->New();
			// Get the pos of the player
			ServerMessage::Vector2f* playerPos = new ServerMessage::Vector2f();
			playerPos->New();
			sf::Vector2f pos = playerData[player]->getPosition();
			playerPos->set_posx(pos.x);
			playerPos->set_posy(pos.y);

			playerInfo->set_allocated_possition(playerPos);

			//get other data for the player
			playerInfo->set_playernumber(player);
			playerInfo->set_playerscore(playerData[player]->getScore());
 			
			std::vector<std::string> f;

			playerInfo->FindInitializationErrors(&f);

			if (f.size() > 0)
			{
				std::cin.get();
			}
			playerInfo->CheckInitialized();

 			gamePlayers[player] = playerInfo;

		}
		// add player data
		// NOTE: due to wanting to keep a constant message size and restrictions with Proto Buffer 
		// Array could not be used thus Hack to send multiplayers
		newMessage->set_allocated_playerone(gamePlayers[0]);
		newMessage->set_allocated_playertwo(gamePlayers[1]); 
	 

		// set final message infromation 
		newMessage->set_playersconnected(numConnectedPlayers);

		newMessage->set_playernumber(client);
		// Get player infromation
		ServerMessage::ServerInformation* serverInfo = new ServerMessage::ServerInformation();

		newMessage->set_allocated_additioanlinfo(additionalInfo);

		serverInfo->set_messagenumber(numOfMessageSend[client]++);
		serverInfo->set_serverinformation(serverVersionNum);
		serverInfo->set_timestamp(networkTimeLapse->gameTime);
		newMessage->set_allocated_serverinfo(serverInfo);

		std::vector<std::string> f;
		newMessage->FindInitializationErrors(&f);
		// Make sure message has got all valid feilds
		newMessage->CheckInitialized();

		std::string messageData;
		newMessage->SerializeToString(&messageData);

		SendMessage(messageData, clientsIPInfo[client]);
	}

 }

void NetworkManager::WorkOutSyncTimingForClient()
{
}

void NetworkManager::SendMessage(std::string data, clientUDPInfo clientUDPInfo)
{
 
	
	ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage;
	newMessage->ParseFromString(data);
	// Send a debug log of message to logging system when in debug mode 
	sf::IpAddress recipient = clientUDPInfo.getIP();
	unsigned short port = clientUDPInfo.getPort();

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
	
		GameLogging::Log("Message Number" + std::to_string(newMessage->serverinfo().messagenumber()) + " for client " + std::to_string(newMessages->playernumber()));
 		//	GameLogging::Log(newMessages->DebugString());

	}
}

std::vector<ClientMessage::ClientMessage*> NetworkManager::lastMessageRecivedClients()
{
	return lastServerMessage;
}

int NetworkManager::getPlayersConnected()
{
	return playerConnected;
}

bool NetworkManager::hasRecivedClientInfo(int clientNumber)
{

	if (clientNumber >= 0 && clientNumber < recivedClientInfo.size())
	{
		return recivedClientInfo[clientNumber];
	}
	return false;
}

void NetworkManager::setHasRecivedClientInfo(int clientNumber, bool value)
{
	if (clientNumber > 0 && clientNumber < recivedClientInfo.size())
	{
		 recivedClientInfo[clientNumber] = value;
	}
}

 

void NetworkManager::ReciveClientInfo()
{
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[100];
	udpSocket.receive(buffer, 100, received, sender, port);

	if (received > 0)
	{

		std::string f = buffer;
		ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();

		newMessage->ParseFromArray(buffer, sizeof(buffer));
		// Send a debug log of message to logging system when in debug mode 
		//GameLogging::Log(newMessage->DebugString());
	
		if (newMessage->clientnumber() != -1)
		{
			recivedClientInfo[newMessage->clientnumber()] = true;
		}

		clientUDPInfo clientRecived = clientUDPInfo(sender, port, clientsIPInfo.size());

		bool clientAlreadyFounds = false;
		for each (auto client in clientsIPInfo)
		{
			if (client.getPort() == clientRecived.getPort() && client.getIP() == clientRecived.getIP())
			{
				clientAlreadyFounds = true;
			}
		}

		// Check if the client is requesting a first connectin
		if (newMessage->addiontalinfo() == ClientMessage::ClientMessage_AdditioanlRequests::ClientMessage_AdditioanlRequests_FirstConnect)
		{


			if (!clientAlreadyFounds)
			{
				// if not already reached the max number of players connected 
				if (playerConnected < NUM_PLAYERS)
				{

					// add the client to list of clients sending data to 
					clientsIPInfo.push_back(clientRecived);


					playerConnected++;		
					
					networkTimeLapse->SendServerConfirmMessage(newMessage->clientinfo().timestamp(),playerConnected - 1, playerConnected, clientRecived.getIP());

				}
			}

		}
		else if (newMessage->addiontalinfo() == ClientMessage::ClientMessage_AdditioanlRequests::ClientMessage_AdditioanlRequests_Disconnect)
		{
			if (clientAlreadyFounds)
			{
		 
				int clientIndex = 0;
				for (; clientIndex < clientsIPInfo.size(); clientIndex++)
				{
					if (clientsIPInfo[clientIndex].getPort() == clientRecived.getPort() && clientsIPInfo[clientIndex].getIP() == clientRecived.getIP())
					{
						clientsIPInfo.erase(clientsIPInfo.begin() + clientIndex);
						numOfMessageSend[clientIndex] = 0;
						break;
					}

				} 
				playerConnected--;
			 
			}
		}
		else
		{
			lastServerMessage[newMessage->clientnumber()] = newMessage;
		}
	}

}
