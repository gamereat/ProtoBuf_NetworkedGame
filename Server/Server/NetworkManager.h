#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include <vector>
#include "ServerController.h"
#include "NetworkTimeLapse.h"
/*
Number of players within a game
*/
const sf::Vector2f playerOneStartingLocation = sf::Vector2f(50, SCREEN_HEIGHT / 2);
const sf::Vector2f playerTwoStartingLocation = sf::Vector2f(SCREEN_WIDTH -50, SCREEN_HEIGHT / 2 );
const sf::Vector2f ballStartPos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

struct clientUDPInfo
{
public:
	sf::IpAddress ip;
	unsigned short port;
	int playerNum;
	clientUDPInfo(sf::IpAddress ip, short port,int playerNum)
	{
		this->playerNum = playerNum;
		this->ip = ip;
		this->port = port;
	}
	inline bool operator==(const clientUDPInfo& lhs )
	{
		if (lhs.ip == this->ip && lhs.port == this->port)
		{
			return true;

		}
		return false;
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
	void  SendServerMessage(int serverVersionNum, class Ball* ball, Player* playerData[NUM_PLAYERS], int numConnectedPlayers);


	void SendMessage(std::string data, clientUDPInfo clientIp);

	std::vector<ClientMessage::ClientMessage*> lastMessageRecivedClients();
	int getPlayersConnected();

	std::vector<bool> recivedClientInfo;

private:



	/*
	Sends time syncing message
	*/
	NetworkTimeLapse* networkTimeLapse;

	/*
	Number of player's current connect to game server
	*/
	int playerConnected;

	/*
	Sends a message with extra data to the client trying to connect with which player it will be and such 
	*/
	void SendInitConnectionInformation(clientUDPInfo newClient);

	/*
	Holds the last server message recived from the server
	*/
	std::vector<ClientMessage::ClientMessage*> lastServerMessage;
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
	Number of messages sent to each client that's connected
	*/
	std::vector<int> numOfMessageSend;
	/*
	UDP socket used to conect to clients
	*/
	sf::UdpSocket udpSocket;

	/*
	Port number being used currently
	*/
	int portNumber;

};

