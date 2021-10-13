#include "../header/Thing.h"
#include <iostream>
#include <string>

void Thing::setName(std::string _name) { name = _name; }
void Thing::setDescription(std::string _description) { description = _description; }
void Thing::setStatus(std::string _status) { status = _status; }
void Thing::setType(std::string _type) { type = _type; }
// void Thing::addBorder(Border* _border) { borders.push_back(_border); }
// void Thing::addItem(Item* _item) { items.push_back(_item); }
// void Thing::addContainer(Container* _container) { containers.push_back(_container); }
// void Thing::addCreature(Creature* _creature) { creatures.push_back(_creature); }
// void Thing::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::string Thing::getName() { return name; }
std::string Thing::getDescription() { return description; }
std::string Thing::getStatus() { return status; }
std::string Thing::getType() { return type; }
// std::vector<Border*> Thing::getBorder() { return borders; }
// std::vector<Item*> Thing::getItem() { return items; }
// std::vector<Container*> Thing::getContainer() { return containers; }
// std::vector<Creature*> Thing::getCreature() { return creatures; }
// std::vector<Trigger*> Thing::getTrigger() { return triggers; }
