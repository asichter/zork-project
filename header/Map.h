#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "Room.h"

class Map {
private:
    std::string name;
    std::string description;
    // Border* border;
    std::vector<Room *> rooms;
    std::vector<Item*> items;
    std::vector<Creature*> creatures;
    std::vector<Container*> containers;

public:
    Map();
    virtual void addRoom(Room * _room);
    virtual void addItem(Item * _item);
    virtual void addCreature(Creature * _creature);
    virtual void addContainer(Container* _container);
};

#endif
