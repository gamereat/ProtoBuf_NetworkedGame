#include "Map.h"



Map::Map()
{


	if (!wallTexture.loadFromFile("../res/art/wall.png"))
	{
		GameLogging::LogError("Failed to load in wall texture");
	}
	else
	{
		wallSprite = sf::Sprite(wallTexture);
	}


	if (!pointTexture.loadFromFile("../res/art/wall.png"))
	{
		GameLogging::LogError("Failed to load in point texture");

	}
	else
	{
		pointSprite = sf::Sprite(pointTexture);
	}



	if (!emptyTexture.loadFromFile("../res/art/wall.png"))
	{
		GameLogging::LogError("Failed to load in empty texture");

	}
	else
	{
		emptySprite = sf::Sprite(emptyTexture);
	}


	// init the map
	for (int mapCol = 0; mapCol < MAP_LENGTH; mapCol++)
	{
	
		std::vector <MapObject> col;
		for (int mapRow = 0; mapRow < MAP_HIGHT; mapRow++)
		{
			
			MapObject obj;
			obj.setTileType(ServerMessage::MapData::MapTile::MapData_MapTile_Point);
 
			obj.setPosition(sf::Vector2f(mapRow*44, mapCol*44));
			col.push_back(obj);
		}
		map.push_back(col);
	}


}


Map::~Map()
{
}

bool Map::Init()
{
	return true;
}

void Map::Render(sf::RenderWindow * renderWindow)
{
	// RenderMap
	for (int mapCol = 0; mapCol < MAP_LENGTH; mapCol++)
	{

		for (int mapRow = 0; mapRow < MAP_HIGHT; mapRow++)
		{
	  
			map.at(mapCol).at(mapRow).Render(renderWindow);

		}
	}
}

void Map::updateMap(std::vector<std::vector<MapObject>> newMap)
{

 

	// init the map
	for (int mapCol = 0; mapCol < MAP_LENGTH; mapCol++)
	{
 
		for (int mapRow = 0; mapRow < MAP_HIGHT; mapRow++)
		{
			map.at(mapCol).at(mapRow) = newMap.at(mapCol).at(mapRow);

			switch (newMap.at(mapCol).at(mapRow).getTileType())
			{
			case ServerMessage::MapData_MapTile::MapData_MapTile_Empty:
				map.at(mapCol).at(mapRow).setSprite(emptySprite);

				break;
			case ServerMessage::MapData_MapTile::MapData_MapTile_Point:
				map.at(mapCol).at(mapRow).setSprite(pointSprite);

				break;
			case ServerMessage::MapData_MapTile::MapData_MapTile_Wall:
				map.at(mapCol).at(mapRow).setSprite(wallSprite);

				break;

			default:
				break;
			}

 
			map.at(mapCol).at(mapRow).setPosition(sf::Vector2f(mapRow * 44, mapCol * 44));
 		}
	}

}

std::vector<std::vector< MapObject>> Map::getMap()
{
 	return map;
}
