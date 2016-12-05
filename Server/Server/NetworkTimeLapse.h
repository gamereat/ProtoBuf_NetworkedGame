#pragma once
#include "SFML\Network.hpp"
#include "../ProroBuferFiles/ProtroHeaders/SyncTimeMessage.pb.h"
#include <vector>
/*
port number clients will listen for time sync messages on
*/
const int TIME_SYNC_PORT_CLIENT = 7779;
const int DEFAULT_PING_TIMEOUT = 1000;
class NetworkTimeLapse
{
public:
	NetworkTimeLapse();
	~NetworkTimeLapse();
	

	void Init();

	void Update();

	/*
	Sends a message to client after they connect to work out lag

	@param clientNumber			The number of the client given by the server
	@param playersConnected		The number of players connected to the server currently
	*/
	void SendServerConfirmMessage(int timestamp,int clientNumber,int playersConnected, sf::IpAddress clientIp);



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
	@Returns	Advarge time in ms to ping ip
	*/
	int RunPingTest(sf::IpAddress ipToPing, int timeOut);

	void SentServerTimeSyncMessage(SyncTimeMessage::ClientConfirmConnect* ,sf::IpAddress clientIp);

	sf::UdpSocket timeSyncSocket;

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
	the time staamp the server starated at
	*/
	clock_t timeServerStarted;


	sf::Clock clock;


};

