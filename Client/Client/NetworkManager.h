#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	
	void Init();

	/*
	Works out when to start the game clock based off server timing 
	*/
	void WorkOutSyncTiming();
	
	void Update();

	void GetPlayerTypeFromServer();

	void ReciveMessageToServer();
	void SentMessageToServer(int clientVersion , ClientMessage::Playerinfromation* playerInfo);
private:

	void SendMessage(std::string );
	/*
	clock that is sycned up with other clients 
	*/
	sf::Clock sycnClock;

	/*
	Port number being used currently
	*/
	int portNumber;

	/*
	Socked used to communicate with the server
	Using UPD to connect with the server
	*/
	sf::UdpSocket updSocket;

	/*
	The number of messages that have been sent to the server
	Increments after each message has been sent 
	used to make sure messages are being recived by the server
	*/
	int numOfMessageSend;

	/*
	The server address of the server
	*/
	sf::IpAddress serverAddress;

	/*
	The port number of the server trying to connect to
	*/
	float serverPort;


};

