#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "Player.h"
#include <vector>
#include "Map.h"

struct clientUDPInfo
{
public:
	sf::IpAddress ip;
	unsigned short port;
	clientUDPInfo(sf::IpAddress ip, short port)
	{
		this->ip = ip;
		this->port = port;
	}
};
class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();



	/*
	Init the server network conection
	*/
	void Init();


	void Update();
	void SendServerMessage(int serverVersionNum, Player players[4], Map map, int numConnectedPlayers);


	void SendMessage(std::string data);

private:

	/*
	Holds the last server message recived from the server
	*/
	std::vector<ClientMessage::ClientMessage> lastServerMessage;
	/*
	Recives data from a client  
	*/
	void ReciveClientInfo();

	/*
	List all active clients ip info
	*/
	std::vector<clientUDPInfo> clientsIPInfo;

	/*
	Send information to client to sync up timings
	*/
	void WorkOutSyncTimingForClient();
	/*
	Number of messages sent
	*/
	int numOfMessageSend;
	/*
	UDP socket used to conect to clients
	*/
	sf::UdpSocket udpSocket;

	/*
	Port number being used currently
	*/
	int portNumber;

};

