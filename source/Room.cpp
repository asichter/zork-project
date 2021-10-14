#include "../header/Room.h"
#include <iostream>
#include <string>

Room::Room() {
    name = "";
    status = "";
    type = "regular";
    description = "";
}

void Room::display() 
{
    if(getName() != "") std::cout << "Room: " << this->getName() << std::endl;
}

// void Room::setStatus(std::string _status) { status = _status; }
// void Room::setType(std::string _type) { type = _type; }
void Room::addBorder(Border* _border) { borders.push_back(_border); }
void Room::addItem(Item* _item) { items.push_back(_item); }
void Room::addContainer(Container* _container) { containers.push_back(_container); }
void Room::addCreature(Creature* _creature) { creatures.push_back(_creature); }
void Room::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

// std::string Room::getStatus() { return status; }
// std::string Room::getType() { return type; }
std::vector<Border*> Room::getBorder() { return borders; }
std::vector<Item*> Room::getItem() { return items; }
std::vector<Container*> Room::getContainer() { return containers; }
std::vector<Creature*> Room::getCreature() { return creatures; }
std::vector<Trigger*> Room::getTrigger() { return triggers; }
