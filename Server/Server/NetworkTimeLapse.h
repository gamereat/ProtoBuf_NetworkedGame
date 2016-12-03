#pragma once
#include "SFML\Network.hpp"
#include "../ProroBuferFiles/ProtroHeaders/SyncTimeMessage.pb.h"
#include <vector>
/*
port number clients will listen for time sync messages on
*/
const int TIME_SYNC_PORT_CLIENT = 7779;
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


	/*
	Gets the time since Epoch
	*/
	int getTimeSinceEpoch();	
	float getTimeSinceLastMessage(int lastMessageTime, int currentTime);


	float estlag;
private:


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


};

