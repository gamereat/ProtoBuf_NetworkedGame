#include "MapObject.h"



MapObject::MapObject()
{
	tileType = ServerMessage::MapData::MapTile::MapData_MapTile_Empty;
}


MapObject::~MapObject()
{
}

void MapObject::setTileType(ServerMessage::MapData::MapTile newTile)
{
	tileType = newTile;
}

ServerMessage::MapData::MapTile MapObject::getTileType()
{
	return tileType;
}
