#include "NetworkTimeLapse.h"
#include <ctime>
#include <iomanip>
#include "GameLogging.h"
#include "../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "ServerController.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

std::vector<int> NetworkTimeLapse::clientLastPingResult = std::vector<int>(NUM_PLAYERS);
int NetworkTimeLapse::  gameTime = 0;
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


	// recaculate the game time
	gameTime = (clock.getElapsedTime().asMilliseconds());


	std::cout << gameTime << std::endl;
	sf::IpAddress sender;;
	std::size_t received = 0;
	unsigned short port;
	char buffer[1024];
	timeSyncSocket.receive(buffer, 1024, received, sender, port);



	if (received > 0)
	{

		SyncTimeMessage::ClientConfirmConnect* clientSync = new SyncTimeMessage::ClientConfirmConnect();

		clientSync->ParseFromArray(buffer, sizeof(buffer));

		if (clientSync->IsInitialized())
		{

			SentServerTimeSyncMessage(clientSync, sender);
		}
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
	
	serverConfimMessage->set_gametimer(gameTime);

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

	clientLastPingResult[clientNumber] = RunPingTest(clientIp, DEFAULT_PING_TIMEOUT);
}

float NetworkTimeLapse::getTimeSinceLastMessage(int lastMessageTime, int currentTime)
{

	// work out diffrence taken to send then recive message 
	return (currentTime - lastMessageTime) / 2;
}

int NetworkTimeLapse::GetClientEsimateLag(int clientNumber)
{
	return clientLastPingResult[clientNumber]  / 2 ;
}

int NetworkTimeLapse::RunPingTest(sf::IpAddress ipToPing,int timeOut)
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
	ServerMessage::Playerinfromation* gamePlayers[NUM_PLAYERS];
	for (int player = 0; player < NUM_PLAYERS; player++)
	{
		gamePlayers[player] = new ServerMessage::Playerinfromation();
	}

	// loop for each player
	for (int player = 0; player < NUM_PLAYERS; player++)
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
	
	std::string SendData ;


	//size of messsage
	int size = fakeServerMess.ByteSize(); 
	fakeServerMess.AppendToString(&SendData);
	 
	// Init Vars for pinging 
	HANDLE handle  = nullptr;
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

void NetworkTimeLapse::SentServerTimeSyncMessage(SyncTimeMessage::ClientConfirmConnect * clientSyncMess, sf::IpAddress clientIp)
{
	 
	SyncTimeMessage::ConnectTime* connectTime = new SyncTimeMessage::ConnectTime();



	connectTime->set_clienttimesinceepoch(clock.getElapsedTime().asMilliseconds());


 
	connectTime->set_gametimer(gameTime);
	int lastMessagTime = playerReciveTimeStamps[clientSyncMess->clientnumber()].back();



	playerReciveTimeStamps[clientSyncMess->clientnumber()].push_back(clientSyncMess->connecttime().timetaketorecivelastmessage());

	connectTime->set_timetaketorecivelastmessage(getTimeSinceLastMessage(lastMessagTime, clock.getElapsedTime().asMilliseconds()));

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

	clientLastPingResult[clientSyncMess->clientnumber()] = (RunPingTest(clientIp, DEFAULT_PING_TIMEOUT));


 }

float NetworkTimeLapse::getTimeSinceServerStarted()
{
	return 0.0f;
}



