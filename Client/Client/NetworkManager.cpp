#include "NetworkManager.h"
#include "GameLogging.h"
#include <google\protobuf\message.h>
 
NetworkManager::NetworkManager()
{

	// Varify protobuf settings
	GOOGLE_PROTOBUF_VERIFY_VERSION;

}


NetworkManager::~NetworkManager()
{
}


void NetworkManager::Init()
{
	numOfMessageSend = 0;
	if (updSocket.bind(54000) != sf::Socket::Done)
	{
		// error...
	}
	updSocket.setBlocking(false);

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

		lastServerMessage = *newMessage;
		// Send a debug log of message to logging system when in debug mode 
		GameLogging::Log(newMessage->DebugString());
	}

}

void NetworkManager::SentMessageToServer(int clientVersion, ClientMessage::Playerinfromation* playerInfo)
{
	// new client message to be sent to server
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage() ;
	newMessage->New();

	// Get the client information
	ClientMessage::ClientInformation clientInfo ;
 	clientInfo.set_clientversion(clientVersion);
	clientInfo.set_messagenumber( numOfMessageSend);
	
	// increase the number of messaage sent
	numOfMessageSend++;

	newMessage->set_allocated_clientinfo(&clientInfo);
	newMessage->set_allocated_playerinfo(playerInfo); 

	// Make sure message has got all valid feilds
	newMessage->CheckInitialized();

 	
 
	std::string messageData; 
	newMessage->SerializeToString(&messageData);

 	SendMessage(messageData);
	 
 }

ServerMessage::ServerMessage NetworkManager::getLastServerMessage()
{
	return lastServerMessage;
}

void NetworkManager::SendMessage(std::string data)
{
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();
	newMessage->ParseFromString(data);
	// Send a debug log of message to logging system when in debug mode 
	GameLogging::Log(newMessage->DebugString());
 	sf::IpAddress recipient = "127.0.0.1";
	unsigned short port = 7777;

 	int size = newMessage->ByteSize();
	GameLogging::Log("Message Length " + std::to_string(size));

	void *buffer = malloc(size);
	newMessage->SerializeToArray(buffer, size);


	if (updSocket.send(buffer, 24, recipient, port) != sf::Socket::Done)
	{
		// error...
	}
	else {
		ClientMessage::ClientMessage* newMessages = new ClientMessage::ClientMessage();
		newMessages->ParseFromArray(buffer, size);
		GameLogging::Log(newMessages->DebugString());

	}
}
