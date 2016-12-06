#pragma once
#include "SFML/Network.hpp"
#include "../../ProroBuferFiles/ProtroHeaders/ClientMessage.pb.h"
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include <vector>
#include "ServerController.h"
#include "NetworkTimeLapse.h"


/*
The starting position of the player one in the game
*/
const sf::Vector2f playerOneStartingLocation = sf::Vector2f(50, SCREEN_HEIGHT / 2);


/*
The starting position of the player two in the game
*/
const sf::Vector2f playerTwoStartingLocation = sf::Vector2f(SCREEN_WIDTH -50, SCREEN_HEIGHT / 2 );

/*
The starting position of the ball in the game
*/
const sf::Vector2f ballStartPos = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

/*
Default port server will use 
*/
const unsigned short SERVER_PORT = 7777;

/*
Client ip information used to send messsage for
*/
struct clientUDPInfo
{
public:

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

	inline void setIp(sf::IpAddress ip) { this->ip = ip; }
	inline void setPort(unsigned short port) { this->port = port; }
	inline void setPlayerNum(int playerNum) { this->playerNum = playerNum; }


	inline sf::IpAddress getIP() { return this->ip; }
	inline unsigned short getPort(){ return port; }
	inline  int getPlayerNum(){ return playerNum; }
private:
	/*
	ip address for client
	*/
	sf::IpAddress ip;

	/*
	Port number for the player
	*/
	unsigned short port;

	/*
	player number of the client
	*/
	int playerNum;
};

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
	Send a server message

	@param serverVersionNum			version number server is running 
	@param ball						the ball object that is flying around world
	@param playerData[NUM_PLAYERS]	information from all the players within the game
	@param numConnectedPlayers		The number of connected players in the game 
	*/
	void  SendServerMessage(int serverVersionNum, class Ball* ball, Player* playerData[NUM_PLAYERS], int numConnectedPlayers);

	/*
	Sends a message to a given client 

	@parma data			data that will be sent to the client
	@param clientIp		the client information that the message should be sent to
	*/
	void SendMessage(std::string data, clientUDPInfo clientIp);


	/*
	Gets the last message recived from a given from clients

	@return vector of messages from each client 
	*/
	std::vector<ClientMessage::ClientMessage*> lastMessageRecivedClients();

	/*
	Gets the number of players connected 

	@return number of players
	*/
	int getPlayersConnected();

	/*
	Has a client connection infomration
	*/
	bool hasRecivedClientInfo(int clientNumber);


	/*
	Has a client connection infomration
	*/
	void setHasRecivedClientInfo(int clientNumber, bool value);
private:


	/*
	has recived infomation about clients
	*/
	std::vector<bool> recivedClientInfo;

	/*
	Sends time syncing message
	*/
	NetworkTimeLapse* networkTimeLapse;

	/*
	Number of player's current connect to game server
	*/
	int playerConnected; 

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

