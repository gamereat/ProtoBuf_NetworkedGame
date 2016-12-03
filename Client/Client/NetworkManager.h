#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "NetworkTimeStart.h"
const sf::Vector2f playerOneStartingLocation = sf::Vector2f(0, 10);
const sf::Vector2f playerTwoStartingLocation = sf::Vector2f(400, 10);

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	
	void Init();

	/*
	Will connect user to the server and get init Message
	*/
	void ConnectToServer();

	/*
	Works out when to start the game clock based off server timing 
	*/
	void WorkOutSyncTiming();
	
	void Update();

	void GetPlayerTypeFromServer();

	void ReciveMessageToServer();
	void SentMessageToServer(int clientVersion , ClientMessage::Playerinfromation* playerInfo, ClientMessage::ClientMessage_AdditioanlRequests additionalRequests);
	
	/*
	Tell the server the client wasnts to disconnect
	*/
	void SendDissconectMessage();
	/*
	Sends a connect message to a server
	*/
	void SentConnectionMessage(int clientVersion);

	ServerMessage::ServerMessage* getLastServerMessage();

	int getNumberMessageRecived();
private:

	NetworkTimeStart networkTimeStart;

	/*
	Client number assigned by the server
	*/
	int clientNumber;

	/*
	Holds the last server message recived from the server
	*/
	ServerMessage::ServerMessage* lastServerMessage;


	void SendMessage(std::string );
	/*
	clock that is sycned up with other clients 
	*/
	sf::Clock sycnClock;

	/*
	Port number being used currently
	*/
	short portNumber;

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

	/*
	Holds the number of message recived 
	*/
	int numOfMessageRecived;

};

