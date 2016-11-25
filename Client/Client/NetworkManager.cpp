#include "NetworkManager.h"
#include "GameLogging.h"
#include <google\protobuf\message.h>


NetworkManager::NetworkManager()
{
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
 
}

void NetworkManager::WorkOutSyncTiming()
{
	//Pesucode of planned syncing
	// 1. Send time stamp to server
	// 2. Get timestamp from server 



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

 	

 
	std::string f; 
	
	int size = newMessage->ByteSize();
	;
GameLogging::Log("Message Length " + std::to_string(size));
newMessage->SerializeToString(&f);
	SendMessage(f);
	 
 }

void NetworkManager::SendMessage(std::string data)
{
	ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();
	newMessage->ParseFromString(data);
	// Send a debug log of message to logging system when in debug mode 
		GameLogging::Log(newMessage->DebugString());

	sf::IpAddress recipient = "127.0.0.1";
	unsigned short port = 7777;
	const char* output = data.c_str();
	sf::Packet p ;
p.
	if (updSocket.send(output, 1024, recipient, port) != sf::Socket::Done)
	{
		// error...
	}
}
