#include "NetworkTimeStart.h"
#include <ctime>
#include <iomanip>
#include "GameLogging.h"


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

		SentClientTimeSyncMessage(serverConfimMess);

		expectingConfirmMessage = false;
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

	connectTime->set_clienttimesinceepoch(getTimeSinceEpoch());
	connectTime->set_timetaketorecivelastmessage(serverConfirmMess->servertimesinceepoch() - getTimeSinceEpoch());

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

float NetworkTimeStart::getTimeSinceEpoch()
{
	double epoch;

	std::time_t t = std::time(nullptr);

	// get the time since epoch
	epoch = difftime(mktime(std::gmtime(&t)), time_t(0));

	return epoch;
}
