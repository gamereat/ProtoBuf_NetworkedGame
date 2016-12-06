#include "NetworkManager.h"
#include "GameLogging.h"
#include <google\protobuf\message.h>
#include "ClientController.h"
NetworkManager::NetworkManager()
{

	// Varify protobuf settings
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// DEFAULT WHEN DOIN LOCAL HOSTS 
	// CHANGE WHEN ON MULTI MACHINES
	serverPort = SERVER_LOCAL_PORT;
	serverAddress = SERVER_LOCAL_IP;
	clientNumber = -1;
}


NetworkManager::~NetworkManager()
{
}


void NetworkManager::Init()
{
	networkTimeStart = new NetworkTimeStart();

	numOfMessageSend = 0;
	numOfMessageRecived = 0;

	// bind server to the ip address gen by the client
	if (updSocket.bind(sf::Socket::AnyPort, ClientController::IpAdress) != sf::Socket::Done)
	{
		// error...

		GameLogging::LogError("UNABLE TO BIND UDP SOCKET");
	}
	else 
	{
		// set into non blocking mode
		updSocket.setBlocking(false);
		lastServerMessage = nullptr;

		// get the port number 
		portNumber = updSocket.getLocalPort();

	}
	//init timeing netwokrer 
	networkTimeStart->Init();
}
 
void NetworkManager::Update()
{
	networkTimeStart->Update();

	ReciveMessageToServer();
}
 

void NetworkManager::ReciveMessageToServer()
{
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;

	//MAX PACKAGES COULD BE IS 256 SHOULD BE A CONSTANT 
	char buffer[256];
	updSocket.receive(buffer, 256, received, sender, port);

	// if new message recived

	if (received > 0)
	{
		std::string f = buffer;
 		ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage();

		newMessage->ParseFromArray(buffer, sizeof(buffer));

		//check if valid message
		if (newMessage->IsInitialized())
		{
			lastServerMessage = newMessage;

			// if first message sent 
			if (newMessage->serverinfo().messagenumber() == 0)
			{
				clientNumber = newMessage->playernumber();
			}

			GameLogging::Log("Message Number" + std::to_string(newMessage->serverinfo().messagenumber()));
			GameLogging::Log("Message Recived" + std::to_string(numOfMessageRecived));

			numOfMessageRecived++;
		}
		// Send a debug log of message to logging system when in debug mode 
		//GameLogging::Log(newMessage->DebugString());
	}

}

void NetworkManager::SentMessageToServer(int clientVersion, ClientMessage::Playerinfromation* playerInfo, ClientMessage::ClientMessage_AdditioanlRequests additionalRequests)
{
	// new client message to be sent to server
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage() ;
	newMessage->New();

	newMessage->set_clientnumber(clientNumber);

	
	// increase the number of messaage sent
	numOfMessageSend++;

	newMessage->set_allocated_playerinfo(playerInfo); 


	newMessage->set_addiontalinfo(additionalRequests);




	// Get the client information
	ClientMessage::ClientInformation clientInfo;
	clientInfo.set_clientversion(clientVersion);
	clientInfo.set_messagenumber(numOfMessageSend);
	clientInfo.set_timestamp(networkTimeStart->gameTime);
	newMessage->set_allocated_clientinfo(&clientInfo);

	// Make sure message has got all valid feilds
	newMessage->CheckInitialized();

 	
 
	std::string messageData; 
	newMessage->SerializeToString(&messageData);

 	SendMessage(messageData);
}

void NetworkManager::SendDissconectMessage()
{
	// new client message to be sent to server
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();
	newMessage->New();


	// increase the number of messaage sent
	numOfMessageSend++;



	ClientMessage::Playerinfromation playerInfo = ClientMessage::Playerinfromation();
	ClientMessage::playerPos* playerPos = new ClientMessage::playerPos();

 	playerPos->set_posx(0);
	playerPos->set_posy(0);
	playerInfo.set_allocated_pos(playerPos);

	//Setting to -1 due to not knowing what player number this client will be yet
	//will find out from first responce message
	playerInfo.set_playernumber(-1);

	newMessage->set_allocated_playerinfo(&playerInfo);

	// Send a connect message
	newMessage->set_addiontalinfo(ClientMessage::ClientMessage_AdditioanlRequests_Disconnect);


	newMessage->set_clientnumber(clientNumber);

	// Get the client information
	ClientMessage::ClientInformation clientInfo;
	clientInfo.set_clientversion(-1);
	clientInfo.set_messagenumber(numOfMessageSend);
	clientInfo.set_timestamp(networkTimeStart->gameTime);

	newMessage->set_allocated_clientinfo(&clientInfo);

	// Make sure message has got all valid feilds
	newMessage->CheckInitialized();
	std::string messageData;
	newMessage->SerializeToString(&messageData);

	SendMessage(messageData);
}

void NetworkManager::SentConnectionMessage(int clientVersion)
{
	// new client message to be sent to server
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();
	newMessage->New();


	ClientMessage::Playerinfromation playerInfo = ClientMessage::Playerinfromation();
	ClientMessage::playerPos* playerPos = new ClientMessage::playerPos();

 	playerPos->set_posx(0);
	playerPos->set_posy(0);
	playerInfo.set_allocated_pos(playerPos);

	//Setting to -1 due to not knowing what player number this client will be yet
	//will find out from first responce message
	playerInfo.set_playernumber(-1);

	newMessage->set_allocated_playerinfo(&playerInfo);

	// Send a connect message
	newMessage->set_addiontalinfo(ClientMessage::ClientMessage_AdditioanlRequests_FirstConnect);

   

	// Get the client information
	ClientMessage::ClientInformation clientInfo;
	clientInfo.set_clientversion(clientVersion);
	clientInfo.set_messagenumber(numOfMessageSend);
	clientInfo.set_timestamp(networkTimeStart->gameTime);

	newMessage->set_clientnumber(clientNumber);
	// increase the number of messaage sent
	numOfMessageSend++;

	newMessage->set_allocated_clientinfo(&clientInfo);

	// Make sure message has got all valid feilds
	newMessage->CheckInitialized();
	std::string messageData;
	newMessage->SerializeToString(&messageData);

	SendMessage(messageData);

	networkTimeStart->setExpectingConfirmMessage();
}

ServerMessage::ServerMessage* NetworkManager::getLastServerMessage()
{
	return lastServerMessage;
}

int NetworkManager::getNumberMessageRecived()
{
	return numOfMessageRecived;
}

NetworkTimeStart * NetworkManager::GetNetworkTimeManger()
{
	return networkTimeStart;
}

void NetworkManager::SendMessage(std::string data)
{
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();
	newMessage->ParseFromString(data);
	// Send a debug log of message to logging system when in debug mode 
//	GameLogging::Log(newMessage->DebugString());

	newMessage->CheckInitialized();
 	sf::IpAddress recipient = serverAddress;
	unsigned short port = serverPort;

	int size = newMessage->ByteSize();
	void *buffer = malloc(size);
	newMessage->SerializeToArray(buffer, size);
	//GameLogging::Log("Message Length " + std::to_string(size));


	if (updSocket.send(buffer, size, recipient, port) != sf::Socket::Done)
	{
		// error...
	}
	else 
	{
		ClientMessage::ClientMessage* newMessages = new ClientMessage::ClientMessage();
		newMessages->ParseFromArray(buffer, size);


	}
}
