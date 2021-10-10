#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Creature.h"
#include "Container.h"
#include "Item.h"
#include "Trigger.h"

class Room {
private:
    std::string name;
    std::string status;
    std::string type;
    std::string description;
    std::string borderN;
    std::string borderE;
    std::string borderW;
    std::string borderS;
    std::vector<Item*> items;
    std::vector<Container*> containers;
    std::vector<Creature*> creatures;
    std::vector<Trigger*> triggers;

public:
    Room(std::string _name, std::string _status, std::string _type, std::string _description, std::string _borderN, std::string _borderE, std::string _borderW, std::string _borderS, std::vector<Item*> _items, std::vector<Container*> _containers, std::vector<Creature*> _creatures, std::vector<Trigger*> _triggers);
};

#endif
