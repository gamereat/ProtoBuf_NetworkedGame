#include "Map.h"



Map::Map()
{

	for (int mapCol = 0; mapCol < MAP_LENGTH; mapCol++)
	{
	
		std::vector <MapObject> col;
		for (int mapRow = 0; mapRow < MAP_HIGHT; mapRow++)
		{
			
			MapObject obj;
			obj.setTileType(ServerMessage::MapData_MapTile::MapData_MapTile_Wall);
			col.push_back(obj);
		}
		map.push_back(col);
	}


}


Map::~Map()
{
}

std::vector<std::vector< MapObject>> Map::getMap()
{
 	return map;
}
