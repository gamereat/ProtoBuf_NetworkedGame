#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"

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

	/*
	Send information to client to sync up timings 
	*/
	void WorkOutSyncTimingForClient();

private:
	
	/*
	UDP socket used to conect to clients
	*/
	sf::UdpSocket udpSocket;

	/*
	Port number being used currently
	*/
	int portNumber;

	char buffer[1024];
};

