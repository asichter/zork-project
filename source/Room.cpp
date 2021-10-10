#include "Room.h"

Room::Room(std::string _name, std::string _status, std::string _type, std::string _description, std::string _borderN, std::string _borderE, std::string _borderW, std::string _borderS, std::vector<Item*> _items, std::vector<Container*> _containers, std::vector<Creature*> _creatures, std::vector<Trigger*> _triggers) {
    name = _name;
    status = _status;
    type = _type;
    description = _description;
    borderN = _borderN;
    borderE = _borderE;
    borderW = _borderW;
    borderS = _borderS;
    items = _items;
    containers = _containers;
    creatures = _creatures;
    triggers = _triggers;
}
