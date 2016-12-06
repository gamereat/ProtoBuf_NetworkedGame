#pragma once
#include "../ProtroHeaders/SyncTimeMessage.pb.h"
#include "SFML\Network.hpp"

/*
Client time sync port
*/
const int CLIENT_TIME_SYNC_PORT_CLIENT = 7779;
/*
Client time sync port
*/
const int SERVER_TIME_SYNC_PORT_CLIENT = 7778;

/*
Default time before time out a being test
*/
const int DEFAULT_PING_TIMEOUT = 1000;

/*
How log in game time between request a new ping test to rework out lag for game
*/
const int TIME_BETWEEN_PING_TESTS = 5000;

/*
Manges time across game times
*/
class NetworkTimeStart
{
public:
	NetworkTimeStart();
	~NetworkTimeStart();




	/*
	Init the network time manged
	*/
	void Init();


	/*
	Updates network time

	*/
	void Update();


	
	/*
	Gets the server confim message from the server
	*/
	void getServerConfirmMessage();
	/*
	Gets a server contect message
	*/
	void getServerConnectMessage();

	/*
	Static game time var for the global game time accross servers
	*/
	static int gameTime;

	/*
	Set that is will be expecting a confirmeation message
	*/
	void setExpectingConfirmMessage();


	/*
	Gets the current lag time from the server
	*/
	int getLagTime();
private:

	/*
	Ammount lag user should expect
	*/
	int lagTime;

	/*
	If client is expecting a confrim message
	*/
	bool expectingConfirmMessage;

	/*
	Sends a client time sync message

	@param syncMess		message containing sync info
	*/
	void SentClientTimeSyncMessage(SyncTimeMessage::ServerConnectConfirm* syncMess);

	/*
	The client number given by the server
	handles reconecting
	*/
	int clientNumber;

	/*
	Works out the diffrence in time from messages being recived and expected time
	*/
	int CaculateTimeDelay(int serverTime, int clientTime);

	/*
	Runs a ping test on the server to get the ping between them

	@param	ipadress	ip of server
	@param  timeout		time before ping test should timeout
	*/
	int RunPingTest(sf::IpAddress ipToPing, int timeOut);

	/*
	Time sync socket used to connect to server to check timmings
	*/
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

 
	/*
	clock used to sync up game time s
	*/
	sf::Clock clock;


	/*
	Clock used to check how long before should recheck ping
	*/
	sf::Clock pingTestTimer;
};

