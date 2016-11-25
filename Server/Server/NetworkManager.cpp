#include "NetworkManager.h"

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

	udpSocket.receive(buffer, 1024, received, sender, port);

	if (received > 0)
	{
		std::string f = buffer;
		std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
		ClientMessage::ClientMessage* newMessage = new ClientMessage::ClientMessage();
		newMessage->ParseFromString(f);
		// Send a debug log of message to logging system when in debug mode 
		GameLogging::Log(newMessage->DebugString());
	}
	
 
}

void NetworkManager::WorkOutSyncTimingForClient()
{
}
