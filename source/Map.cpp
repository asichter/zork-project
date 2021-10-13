#include "../header/Map.h"

Map::Map() {}

void Map::addRoom(Room* _room)
{
    rooms.push_back(_room);
}
