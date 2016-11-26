#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include"MapObject.h"

#include <vector>

const int MAP_LENGTH = 10;
const int MAP_HIGHT = 10;

class Map
{
public:
	Map();
	~Map();

	
	std::vector<std::vector< MapObject> >getMap();
private:

	/*
	Map that will be sent to the players and can be moved around 
	*/
	std::vector<std::vector< MapObject>> map;

};

