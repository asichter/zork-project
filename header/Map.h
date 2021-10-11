#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "Room.h"

class Map {
private:
    std::vector<Room*> rooms;
    std::vector<Item*> items;
    std::vector<Creature*> creatures;
    std::vector<Container*> containers;

public:
    Map(std::vector<Room*> _rooms, std::vector<Item*> _items, std::vector<Creature*> _creatures, std::vector<Container*> _containers);
};

#endif
