#pragma once
#include "../../ProroBuferFiles/ProtroHeaders/ServerMessage.pb.h"
#include "GameObject.h"
class MapObject : public GameObject
{
public:
	MapObject();
	~MapObject();
	
	virtual void Init() ;
	virtual void Update(float deltaTime) ;
	virtual void Render(sf::RenderWindow*) ;

	

 	void setTileType(ServerMessage::MapData::MapTile);
	ServerMessage::MapData::MapTile getTileType();

	
private:
	virtual void HandleInput(float deltaTime) ;

	/*
	the type of object to represent the tile
	*/
	ServerMessage::MapData::MapTile tileType;
};

