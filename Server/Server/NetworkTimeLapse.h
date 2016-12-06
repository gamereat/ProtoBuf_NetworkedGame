#pragma once
#include "SFML\Network.hpp"
#include "../ProroBuferFiles/ProtroHeaders/SyncTimeMessage.pb.h"
#include <vector>
/*
port number clients will listen for time sync messages on
*/
const int TIME_SYNC_PORT_CLIENT = 7779;

/*
Default time before time out a being test
*/
const int DEFAULT_PING_TIMEOUT = 1000;

/*
How log in game time between request a new ping test to rework out lag for game
*/
const int TIME_BETWEEN_PING_TESTS = 5000;

/*
Default port the time sync server will befound on
*/
const unsigned short DEFAULT_TIME_SYNC_PORT = 7778;

/*
Manges time across game times 
*/
class NetworkTimeLapse
{
public:
	NetworkTimeLapse();
	~NetworkTimeLapse();
	
	/*
	Init the network time manged
	*/
	void Init();

	/*
	Updates network time 

	@prama	clientsIPInfo	all the currently connect players
	*/	
	void Update(std::vector<class clientUDPInfo> clientsIPInfo);

	/*
	Sends a message to client after they connect to work out lag

	@param clientNumber			The number of the client given by the server
	@param playersConnected		The number of players connected to the server currently
	*/
	void SendServerConfirmMessage(int timestamp,int clientNumber,int playersConnected, sf::IpAddress clientIp);


	/*
	Gets
	*/
	float getTimeSinceLastMessage(int lastMessageTime, int currentTime);


	/*
	@retuns		returns last ping test to the client int seconds  
	*/
	static int GetClientEsimateLag(int clientNumber);


	/*
	The current time for the game. Each client is synced up to this
	*/
	static int gameTime;

private:


	/*
	Holds the last ping res	
	*/
	static std::vector<int> clientLastPingResult;

	/*
	Runs a ping test to a given ip adress to work out lag

	@Returns	Advarge time in ms to ping ip
	*/
	int RunPingTest(sf::IpAddress ipToPing, int timeOut);


	/*
	Send A server time sync message to a client

	@param clientConnectionMessage the message received from client stating it wants to connect

	@pram clientIp ip address of client connecting
	*/
	void SentServerTimeSyncMessage(SyncTimeMessage::ClientConfirmConnect* clientConnectionMessage ,sf::IpAddress clientIp);

	/*
	UDP socket used to sync time up with client
	*/
	sf::UdpSocket timeSyncSocket;

	/*
	Port number time socket is bound to
	*/
	float portNumber;


	/*
	Gets the time since the server started 
	*/
	float getTimeSinceServerStarted();

	/*
	Record of time send points for each client 
	*/
	std::vector<std::vector<int>> playerReciveTimeStamps;
 

	/*
	Clock used to work out gametime
	*/
	sf::Clock clock;

	/*
	Clock used to work out when new lag test should be done 
	*/
	sf::Clock pingTestClock;

};

