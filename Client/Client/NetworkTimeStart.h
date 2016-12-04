#pragma once
#include "../ProtroHeaders/SyncTimeMessage.pb.h"
#include "SFML\Network.hpp"

const int TIME_SYNC_PORT_CLIENT = 7779;

class NetworkTimeStart
{
public:
	NetworkTimeStart();
	~NetworkTimeStart();


	void Update();

	void Init();

	void getServerConfirmMessage();
	void getServerConnectMessage();

	float getTimeSinceEpoch();

	void setExpectingConfirmMessage();
private:

	bool expectingConfirmMessage;

	void SentClientTimeSyncMessage(SyncTimeMessage::ServerConnectConfirm*);
	
	int clientNumber;

	/*
	Works out the diffrence in time from messages being recived and expected time
	*/
	int CaculateTimeDelay(int serverTime, int clientTime);

	sf::UdpSocket timeSyncSocket; 


	/*
	Server IP address
	*/
	sf::IpAddress serverIP;

	/*
	Server time sync port
	*/
	unsigned short timeSyncServerPort;

	 
	/*
	Time since the game has started 
	*/
	float gameLapseTimer;

	/*
	The time the server started on based off Epoch
	*/
	float serverStartTime;

 

};

