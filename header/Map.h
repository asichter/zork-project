#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "Room.h"

class Map {
private:
    std::vector<Room*> rooms;

public:
    Map(std::vector<Room*> _rooms);
};

#endif
