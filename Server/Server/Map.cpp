#include "Map.h"



Map::Map()
{

	for (int mapCol = 0; mapCol < MAP_LENGTH; mapCol++)
	{
	
		std::vector <MapObject> col;
		for (int mapRow = 0; mapRow < MAP_HIGHT; mapRow++)
		{
			
			MapObject obj;
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
