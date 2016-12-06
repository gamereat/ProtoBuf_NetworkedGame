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

	// Delete all of my memory's 
	if (networkTimeLapse)
	{
		delete networkTimeLapse;
		networkTimeLapse = nullptr;
	}

	for (auto mess : lastServerMessage)
	{
		delete mess;
		mess = nullptr;
	}

	// i've given all my memorys away :'( 
}

void NetworkManager::Init()
{
	// Init the network time manager
	networkTimeLapse->Init();


	// bind the server to the standard port
	if(udpSocket.bind(portNumber) != sf::Socket::Done)
	{
		GameLogging::LogError(" Failed to bind udp socket   ");
		
		// no point continuing if socket failed to bind 
		return;
	}

	// Only use a non blocking mode 
	udpSocket.setBlocking(false);

	recivedClientInfo = std::vector<bool>(NUM_PLAYERS);
}

void NetworkManager::Update()
{
	// Update game clock 
	networkTimeLapse->Update();

	// check for any new 
	ReciveClientInfo();
 
}
void NetworkManager::SendServerMessage(int serverVersionNum, Ball* ball,Player* playerData[NUM_PLAYERS], int numConnectedPlayers)
{
	// Send messages to all connected clients 
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

		// TODO: NO LONGER USED NEEDS REMOVED FROM BUFFER
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


		// Make sure message has got all valid feilds
		newMessage->CheckInitialized();

		std::string messageData;

		newMessage->SerializeToString(&messageData);

		SendMessage(messageData, clientsIPInfo[client]);
	}

 }
 
void NetworkManager::SendMessage(std::string data, clientUDPInfo clientUDPInfo)
{
 
	ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage;
	newMessage->ParseFromString(data);

	// Send a debug log of message to logging system when in debug mode 
	sf::IpAddress recipient = clientUDPInfo.getIP();
	unsigned short port = clientUDPInfo.getPort();

	// Get the size of message being sent 
	int size = newMessage->ByteSize();
	void *buffer = malloc(size);

	// serialise into the buffer 
	newMessage->SerializeToArray(buffer, size);
	
	GameLogging::Log("Message Length " + std::to_string(size));
	
	// send message to the client requiring it 
	if (udpSocket.send(buffer, size, recipient, port) != sf::Socket::Done)
	{
		GameLogging::LogError("Message was unable to send to " + clientUDPInfo.getIP().toString() + ":" + std::to_string(clientUDPInfo.getPort()));
 	}
	else
	{
  	
		GameLogging::Log("Message Number" + std::to_string(newMessage->serverinfo().messagenumber()) + " for client " + std::to_string(newMessage->playernumber()));
 
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
	// Check if reciving a message
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;

	// Know my binary will never get over this number of bytes
	// TODO: MAKE A CONSTANT 
	char buffer[256];

	udpSocket.receive(buffer, 256, received, sender, port);

	if (received > 0)
	{

		std::string f = buffer;
		ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();

		newMessage->ParseFromArray(buffer, sizeof(buffer));
		// Send a debug log of message to logging system when in debug mode 
		//GameLogging::Log(newMessage->DebugString());
	
		// Check if a valid message
		// should help solve most issue with corrupt packages as will have change binary format needed for proto buff. 
		// NOTE: does solve a lot of corrupt messages but still need addiational checks 
		if (newMessage->IsInitialized())
		{
			// check if a client has not been assigned a number 
			if (newMessage->clientnumber() != -1)
			{
				// set it to get a new client number 
				recivedClientInfo[newMessage->clientnumber()] = true;
			}

			// set up client data that package been recived from
			clientUDPInfo clientRecived = clientUDPInfo(sender, port, clientsIPInfo.size());

			// find out if client is already been tracked or if it's new
			// 
			// will find clients thinking there still conected when server does go down 
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

						networkTimeLapse->SendServerConfirmMessage(newMessage->clientinfo().timestamp(), playerConnected - 1, playerConnected, clientRecived.getIP());

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
				// set the last messsage recived by the client to this message
				lastServerMessage[newMessage->clientnumber()] = newMessage;
			}
		}
	}

}
