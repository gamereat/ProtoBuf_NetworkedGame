#include "NetworkTimeLapse.h"
#include <ctime>
#include <iomanip>
#include "GameLogging.h"

NetworkTimeLapse::NetworkTimeLapse()
{
	portNumber = 7778;

	playerReciveTimeStamps = std::vector<std::vector<int>>(2);

}


NetworkTimeLapse::~NetworkTimeLapse()
{
}

void NetworkTimeLapse::Init()
{
	if (timeSyncSocket.bind(portNumber) != sf::Socket::Done)
	{
		GameLogging::LogError(" Failed to bind udp socket");
	}
	timeSyncSocket.setBlocking(false);
}

void NetworkTimeLapse::Update()
{

	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[1024];
	timeSyncSocket.receive(buffer, 1024, received, sender, port);



	if (received > 0)
	{

		SyncTimeMessage::ClientConfirmConnect* clientSync = new SyncTimeMessage::ClientConfirmConnect();

		clientSync->ParseFromArray(buffer, sizeof(buffer));

		SentServerTimeSyncMessage(clientSync, sender);
	}
}

void NetworkTimeLapse::SendServerConfirmMessage(int timestamp, int clientNumber, int playersConnected, sf::IpAddress clientIp)
{
	SyncTimeMessage::ServerConnectConfirm* serverConfimMessage = new SyncTimeMessage::ServerConnectConfirm();

	// Get time server started at
	float timeStarted = getTimeSinceServerStarted();
	
	serverConfimMessage->set_serverstarttime(timeStarted);

	//Set the clients numbers and players connected

	serverConfimMessage->set_playernumber(clientNumber);
	serverConfimMessage->set_playersconnected(playersConnected);

	//Get time stamp
	
	serverConfimMessage->set_servertimesinceepoch(getTimeSinceEpoch());

	// add time to message time log 

	playerReciveTimeStamps[clientNumber].push_back(timestamp);

	//send message 

	int size = serverConfimMessage->ByteSize();
	void *buffer = malloc(size);
	serverConfimMessage->SerializeToArray(buffer, size);
	GameLogging::Log("Message Length " + std::to_string(size));


	if (timeSyncSocket.send(buffer, 256, clientIp, TIME_SYNC_PORT_CLIENT) != sf::Socket::Done)
	{
		// error...
	}
	else
	{ 
		GameLogging::Log("Time Sync Message sent ");

	}
}

float NetworkTimeLapse::getTimeSinceLastMessage(int lastMessageTime, int currentTime)
{

	// work out diffrence taken to send then recive message 
	return (currentTime - lastMessageTime) / 2;
}

void NetworkTimeLapse::SentServerTimeSyncMessage(SyncTimeMessage::ClientConfirmConnect * clientSyncMess, sf::IpAddress clientIp)
{
	 
	SyncTimeMessage::ConnectTime* connectTime = new SyncTimeMessage::ConnectTime();



	connectTime->set_clienttimesinceepoch(getTimeSinceEpoch());


 

	int lastMessagTime = playerReciveTimeStamps[clientSyncMess->clientnumber()].back();



	playerReciveTimeStamps[clientSyncMess->clientnumber()].push_back(clientSyncMess->connecttime().timetaketorecivelastmessage());

	connectTime->set_timetaketorecivelastmessage(getTimeSinceLastMessage(lastMessagTime, getTimeSinceEpoch()));

	int size = connectTime->ByteSize();
	void *buffer = malloc(size);
	connectTime->SerializeToArray(buffer, size);
	GameLogging::Log("Message Length " + std::to_string(size));


	if (timeSyncSocket.send(buffer, 256, clientIp, TIME_SYNC_PORT_CLIENT) != sf::Socket::Done)
	{
		// error...
	}
	else
	{
		GameLogging::Log("Time Sync Message sent ");

	}



	estlag = getTimeSinceEpoch() - clientSyncMess->connecttime().timetaketorecivelastmessage();
}

float NetworkTimeLapse::getTimeSinceServerStarted()
{
	return 0.0f;
}


int NetworkTimeLapse::getTimeSinceEpoch()
{
	int epoch;

	std::time_t t = std::time(nullptr);

	// get the time since epoch
	epoch = difftime(mktime(std::gmtime(&t)), time_t(0));

	return epoch;
}
