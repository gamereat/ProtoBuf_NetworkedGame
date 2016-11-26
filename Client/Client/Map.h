#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include"MapObject.h"
#include "GameLogging.h"
#include <vector>

const int MAP_LENGTH = 10;
const int MAP_HIGHT = 10;

class Map
{
public:
	Map();
	~Map();

	bool Init();
	
	void Render(sf::RenderWindow* renderWindow);


	void updateMap(std::vector<std::vector< MapObject>> map);

	std::vector<std::vector< MapObject> >getMap();
private:

	/*
	Map that will be sent to the players and can be moved around 
	*/
	std::vector<std::vector< MapObject>> map;

	/*
	texture used to represent wall
	*/
	sf::Sprite wallSprite;
	/*
	texture used to represent empty
	*/
	sf::Sprite emptySprite;
	/*
	texture used to represent points
	*/
	sf::Sprite pointSprite;



	sf::Texture wallTexture;
	sf::Texture pointTexture;
	sf::Texture emptyTexture;

};

