#include "NetworkTimeStart.h"
#include <ctime>
#include <iomanip>
#include "GameLogging.h"

int NetworkTimeStart::gameTime = 0;
NetworkTimeStart::NetworkTimeStart()
{
	timeSyncServerPort = 7778;
	serverIP = "127.0.0.1";
	expectingConfirmMessage = false;
 }


NetworkTimeStart::~NetworkTimeStart()
{

}

void NetworkTimeStart::Update()
{
	if (expectingConfirmMessage)
	{
		getServerConfirmMessage();
	}

	gameTime  = (clock.getElapsedTime().asMilliseconds() - serverStartTime);
}

void NetworkTimeStart::Init()
{
	if (timeSyncSocket.bind(TIME_SYNC_PORT_CLIENT) != sf::Socket::Done)
	{
		// error...
	}
	else
	{ 
	} 
	timeSyncSocket.setBlocking(false);

}

void NetworkTimeStart::getServerConfirmMessage()
{

	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[1024];
	timeSyncSocket.receive(buffer, 1024, received, sender, port);



	if (received > 0)
	{
   
		SyncTimeMessage::ServerConnectConfirm* serverConfimMess = new SyncTimeMessage::ServerConnectConfirm();

		serverConfimMess->ParseFromArray(buffer, sizeof(buffer));

		clientNumber = serverConfimMess->playernumber();

		serverStartTime = serverConfimMess->serverstarttime() + serverConfimMess->gametimer();

		SentClientTimeSyncMessage(serverConfimMess);

		expectingConfirmMessage = false;
	}
}

void NetworkTimeStart::getServerConnectMessage()
{
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[1024];
	timeSyncSocket.receive(buffer, 1024, received, sender, port);



	if (received > 0)
	{

		SyncTimeMessage::ConnectTime* connectMess = new SyncTimeMessage::ConnectTime();

		connectMess->ParseFromArray(buffer, sizeof(buffer));



	}
}

void NetworkTimeStart::setExpectingConfirmMessage()
{
	expectingConfirmMessage = true;
}

void NetworkTimeStart::SentClientTimeSyncMessage(SyncTimeMessage::ServerConnectConfirm * serverConfirmMess)
{
	SyncTimeMessage::ClientConfirmConnect* clientConfim = new SyncTimeMessage::ClientConfirmConnect();
	
	
	clientConfim->set_clientnumber(clientNumber);

	SyncTimeMessage::ConnectTime* connectTime = new SyncTimeMessage::ConnectTime();

	connectTime->set_clienttimesinceepoch(gameTime);
	connectTime->set_timetaketorecivelastmessage(gameTime - serverConfirmMess->gametimer());

	clientConfim->set_allocated_connecttime(connectTime);

	int size = clientConfim->ByteSize();
	void *buffer = malloc(size);
	clientConfim->SerializeToArray(buffer, size);
	GameLogging::Log("Message Length " + std::to_string(size));


	if (timeSyncSocket.send(buffer, 256, serverIP, timeSyncServerPort) != sf::Socket::Done)
	{
		// error...
	}
	else
	{
		GameLogging::Log("Time Sync Message sent ");
	}

 }


int NetworkTimeStart::CaculateTimeDelay(int serverTime, int clientTime)
{
 

	// work out diffrence taken to send then recive message 
	return (clientTime - serverTime) / 2;
}

 

