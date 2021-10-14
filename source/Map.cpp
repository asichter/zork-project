#include "../header/Map.h"

Map::Map() {}

void Map::addRoom(Room* _room) { rooms.push_back(_room); }
void Map::addItem(Item* _item) { items.push_back(_item); }
void Map::addCreature(Creature* _creature) { creatures.push_back(_creature); }
void Map::addContainer(Container* _container) { containers.push_back(_container); }

std::vector<Room*> Map::getRooms() { return rooms; }
std::vector<Item*> Map::getItems() { return items; }
std::vector<Creature*> Map::getCreatures() { return creatures; }
std::vector<Container*> Map::getContainers() { return containers; }

void Map::display() { std::cout << "Map: found map with " << getRooms().size() << " rooms" << std::endl; }

void Map::printRooms() {
    std::cout << std::endl;
    for(unsigned int i = 0; i < rooms.size(); i++) {
        rooms[i]->printRoom();
    }
}