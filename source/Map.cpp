#include "../header/Map.h"

Map::Map() {}

void Map::addRoom(Room* _room) { rooms.push_back(_room); }
void Map::addItem(Item* _item) { items.push_back(_item); }
void Map::addCreature(Creature* _creature) { creatures.push_back(_creature); }
void Map::addContainer(Container* _container) { containers.push_back(_container); }
std::vector<Room*> Map::getRooms() { return rooms; }
void Map::display() { std::cout << "Map: found map with " << getRooms().size() << " rooms" << std::endl; }