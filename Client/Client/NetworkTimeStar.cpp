#include "NetworkTimeStart.h"
#include <ctime>
#include <iomanip>
#include "GameLogging.h"
#include "../ProtroHeaders/ServerMessage.pb.h"
#include "ClientController.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")
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
	gameTime  = (clock.getElapsedTime().asMilliseconds() + serverStartTime + lagTime);

	std::cout << gameTime << '\n';
}

void NetworkTimeStart::Init()
{
	if (timeSyncSocket.bind(TIME_SYNC_PORT_CLIENT, ClientController::IpAdress) != sf::Socket::Done)
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
		lagTime =  RunPingTest(sender, 1000);
		SyncTimeMessage::ServerConnectConfirm* serverConfimMess = new SyncTimeMessage::ServerConnectConfirm();
	clock.restart();

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
	connectTime->set_gametimer(gameTime);
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

 

int NetworkTimeStart::RunPingTest(sf::IpAddress ipToPing, int timeOut)
{
	// Create a fake message that size can be found from to ping with 
	// Due to how protocal buff2  works unable to just work out size without data 
	ServerMessage::ServerMessage fakeServerMess;

	ServerMessage::AdditionalInformation* additionalInfo = new ServerMessage::AdditionalInformation();

	ServerMessage::BallInformation* ballInfo = new ServerMessage::BallInformation();

	ServerMessage::ServerInformation* serverInfo = new ServerMessage::ServerInformation();

	ServerMessage::Vector2f* ballPos = new ServerMessage::Vector2f();
	ServerMessage::Vector2f* ballVelocity = new ServerMessage::Vector2f();

	ballPos->set_posx(0);
	ballPos->set_posy(0);

	ballVelocity->set_posx(0);
	ballVelocity->set_posy(0);

	ballInfo->set_angle(0);
	ballInfo->set_allocated_possition(ballPos);
	ballInfo->set_allocated_velocity(ballVelocity);

	fakeServerMess.set_allocated_ballinformation(ballInfo);

	//Get player infromation
	ServerMessage::Playerinfromation* gamePlayers[2];
	for (int player = 0; player < 2; player++)
	{
		gamePlayers[player] = new ServerMessage::Playerinfromation();
	}

	// loop for each player
	for (int player = 0; player < 2; player++)
	{
		ServerMessage::Playerinfromation* playerInfo = gamePlayers[player];
		ServerMessage::Vector2f* playerPos = new ServerMessage::Vector2f();
		playerPos->set_posx(0);
		playerPos->set_posy(0);

		playerInfo->set_allocated_possition(playerPos);

		//get other data for the player
		playerInfo->set_playernumber(player);
		playerInfo->set_playerscore(0);

		gamePlayers[player] = playerInfo;

	}


	fakeServerMess.set_allocated_playerone(gamePlayers[0]);
	fakeServerMess.set_allocated_playertwo(gamePlayers[1]);


	// set final message infromation 
	fakeServerMess.set_playersconnected(0);

	fakeServerMess.set_playernumber(0);

	fakeServerMess.set_allocated_additioanlinfo(additionalInfo);

	serverInfo->set_messagenumber(0);
	serverInfo->set_serverinformation(0);
	serverInfo->set_timestamp(0);
	fakeServerMess.set_allocated_serverinfo(serverInfo);

	std::string SendData;


	//size of messsage
	int size = fakeServerMess.ByteSize();
	fakeServerMess.AppendToString(&SendData);

	// Init Vars for pinging 
	HANDLE handle = nullptr;
	LPVOID buffer = nullptr;
	DWORD pingRerturnData = DWORD();
	DWORD replySize = DWORD();
	PICMP_ECHO_REPLY pIcmpEchoReply = nullptr;

	handle = IcmpCreateFile();

	// Work out reply size 
	replySize = sizeof(ICMP_ECHO_REPLY) + strlen(SendData.c_str()) + 1;

	// Build buffer
	buffer = (VOID*)malloc(replySize);

	// fill buffer memory
	memset(buffer, 0, replySize);

	// cast to a ping reply info
	pIcmpEchoReply = (PICMP_ECHO_REPLY)buffer;



	//https://msdn.microsoft.com/en-us/library/aa366050(VS.85).aspx
	// send ping request 
	pingRerturnData = IcmpSendEcho2(handle, NULL, NULL, NULL,
		inet_addr(ipToPing.toString().c_str()),
		(char *)SendData.c_str(), strlen(SendData.c_str()),
		NULL, buffer,
		replySize,
		timeOut);

	if (pingRerturnData != 0) {

		GameLogging::Log("Pinged " + ipToPing.toString() + "  round tip time " + std::to_string(pIcmpEchoReply->RoundTripTime));

	}
	else {
		printf("Call to IcmpSendEcho() failed.\n");
		printf("Error: %ld\n", GetLastError());
	}

	IcmpCloseHandle(handle);


	return pIcmpEchoReply->RoundTripTime;
}