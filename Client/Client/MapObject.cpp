#include "MapObject.h"



MapObject::MapObject()
{
	tileType = ServerMessage::MapData::MapTile::MapData_MapTile_Empty;
}


MapObject::~MapObject()
{
}

void MapObject::Init()
{
}


void MapObject::Render(sf::RenderWindow * renderWindow)
{
	renderWindow->draw(sprite);
}

void MapObject::setTileType(ServerMessage::MapData::MapTile newTile)
{
	tileType = newTile;
}

ServerMessage::MapData::MapTile MapObject::getTileType()
{
	return tileType;
}

void MapObject::HandleInput(float deltaTime)
{
	// Tiles don't need input
}

void MapObject::Update(float deltaTime)
{
	// Tiles don't need updating
}