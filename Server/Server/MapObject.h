#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "GameObject.h"
class MapObject
{
public:
	MapObject();
	~MapObject();
	
	void setTileType(ServerMessage::MapData::MapTile);
	ServerMessage::MapData::MapTile getTileType();

private:

	/*
	the type of object to represent the tile
	*/
	ServerMessage::MapData::MapTile tileType;
};

