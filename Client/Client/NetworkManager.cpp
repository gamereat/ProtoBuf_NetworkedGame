#include "NetworkManager.h"
#include "GameLogging.h"
#include <google\protobuf\message.h>
 
NetworkManager::NetworkManager()
{

	// Varify protobuf settings
	GOOGLE_PROTOBUF_VERIFY_VERSION;


	serverPort = 7777;
	serverAddress = "127.0.0.1";
	clientNumber = -1;
}


NetworkManager::~NetworkManager()
{
}


void NetworkManager::Init()
{
	numOfMessageSend = 0;
	numOfMessageRecived = 0;

	if (updSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		// error...
	}
	else 
	{
		updSocket.setBlocking(false);
		lastServerMessage = nullptr;

		// get the port number 
		portNumber = updSocket.getLocalPort();

	}
}

void NetworkManager::ConnectToServer()
{
}

void NetworkManager::WorkOutSyncTiming()
{
	//Pesucode of planned syncing
	// 1. Send time stamp to server
	// 2. Get timestamp from server 



}

void NetworkManager::Update()
{
	ReciveMessageToServer();
}

void NetworkManager::GetPlayerTypeFromServer()
{
}

void NetworkManager::ReciveMessageToServer()
{
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[1024];
	updSocket.receive(buffer, 1024, received, sender, port);



	if (received > 0)
	{
		std::string f = buffer;
		std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
		ServerMessage::ServerMessage* newMessage = new ServerMessage::ServerMessage();

		newMessage->ParseFromArray(buffer, sizeof(buffer));

		lastServerMessage = newMessage;

		// if first message sent 
		if (newMessage->serverinfo().messagenumber() == 0)
		{
			clientNumber = newMessage->playernumber();
		}

		GameLogging::Log("Message Number" +std::to_string( newMessage->serverinfo().messagenumber()));
		GameLogging::Log("Message Recived" + std::to_string(numOfMessageRecived));
		numOfMessageRecived++;

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

	// Get the client information
	ClientMessage::ClientInformation clientInfo ;
 	clientInfo.set_clientversion(clientVersion);
	clientInfo.set_messagenumber( numOfMessageSend);
	
	// increase the number of messaage sent
	numOfMessageSend++;

	newMessage->set_allocated_clientinfo(&clientInfo);
	newMessage->set_allocated_playerinfo(playerInfo); 


	newMessage->set_addiontalinfo(additionalRequests);

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

	// Get the client information
	ClientMessage::ClientInformation clientInfo;
	clientInfo.set_clientversion(-1);
	clientInfo.set_messagenumber(numOfMessageSend);

	// increase the number of messaage sent
	numOfMessageSend++;

	newMessage->set_allocated_clientinfo(&clientInfo);


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

	// Get the client information
	ClientMessage::ClientInformation clientInfo;
	clientInfo.set_clientversion(clientVersion);
	clientInfo.set_messagenumber(numOfMessageSend);
	
	newMessage->set_clientnumber(clientNumber);
	// increase the number of messaage sent
	numOfMessageSend++;

	newMessage->set_allocated_clientinfo(&clientInfo);

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

   


	// Make sure message has got all valid feilds
	newMessage->CheckInitialized();
	std::string messageData;
	newMessage->SerializeToString(&messageData);

	SendMessage(messageData);
}

ServerMessage::ServerMessage* NetworkManager::getLastServerMessage()
{
	return lastServerMessage;
}

int NetworkManager::getNumberMessageRecived()
{
	return numOfMessageRecived;
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
	else {
		ClientMessage::ClientMessage* newMessages = new ClientMessage::ClientMessage();
		newMessages->ParseFromArray(buffer, size);


	}
}
