#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "NetworkTimeStart.h"
 

const sf::IpAddress SERVER_LOCAL_IP = "127.0.0.1";
const unsigned short SERVER_LOCAL_PORT = 7777;

/*
Network manager control all network controlling within the game
*/
class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();
	
	/*
	Init the server network conection
	*/
	void Init();
 
	/*
	Update network events
	Looks for new packages coming in
	*/
	void Update();

 
	/*
	Gets a new message from the server
	*/
	void ReciveMessageToServer();
	
	/*
	Send a new message to the server

	@param clientVersion		The client number

	@param playerInfo			Information for the user controller player
	@param additionalRequests	any additioanl requests from the server
	*/
	void SentMessageToServer(int clientVersion , ClientMessage::Playerinfromation* playerInfo, ClientMessage::ClientMessage_AdditioanlRequests additionalRequests);
	
	/*
	Tell the server the client wasnts to disconnect
	*/
	void SendDissconectMessage();
	/*
	Sends a connect message to a server
	*/
	void SentConnectionMessage(int clientVersion);

	/*
	Gets the latests message sent from the server
	*/
	ServerMessage::ServerMessage* getLastServerMessage();

	/*
	Gets the number of messages recived
	*/
	int getNumberMessageRecived();


	/*
	Gets the network time manger
	*/
	NetworkTimeStart* GetNetworkTimeManger();

private:

	/*
	Netwokr time start controller deals with timing and the server
	*/
	NetworkTimeStart* networkTimeStart;

	/*
	Client number assigned by the server
	*/
	int clientNumber;

	/*
	Holds the last server message recived from the server
	*/
	ServerMessage::ServerMessage* lastServerMessage;


	/*
	Sends data to the server

	@param	data	data require to send 
	*/
	void SendMessage(std::string data);

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

