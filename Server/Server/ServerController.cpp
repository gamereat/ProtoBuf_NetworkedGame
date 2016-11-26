#include "ServerController.h"
#include "GameLogging.h"


ServerController::ServerController()
{
}


ServerController::~ServerController()
{
}

bool ServerController::Init()
{
	if (!standardFont.loadFromFile("../res/font/Politik.otf"))
	{
		GameLogging::LogError("Standard font faile to load");
	//	return false;
	}

	severVersionNumberText.setFont(standardFont);

	//TODO: load version number from file
	//HACK: CURRENT HARD CODED V NUMBER
	severVersionNumberText.setString("Server: (0.0.2)");

	severVersionNumberText.setPosition(715, 0);
	severVersionNumberText.setCharacterSize(24);

	severVersionNumberText.setFillColor(sf::Color::Red);
	networkManger.Init();

	Player* players[4];
	Map* map;
	map = new Map();
	int i = 0;
	for each (auto player in players)
	{
		player = new Player(0, ServerMessage::Playerinfromation::PlayerType::Playerinfromation_PlayerType_Ghost, sf::Vector2f(0, 10));
		players[i] = player;
		i++;
	}
	networkManger.SendServerMessage(2, *players, *map, 4);

	return true;
}

bool ServerController::Update()
{


	return true;
}