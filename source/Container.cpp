#include "../header/Container.h"
#include <iostream>
#include <string>

Container::Container() {}
Container::~Container() {}

void Container::display() { if(getName() != "") std::cout << "Container: " << getName() << std::endl; }

void Container::addAccepts(std::string _accept) {accepts.push_back(_accept); }
void Container::addItem(Item* _item) { items.push_back(_item); }
void Container::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::vector<std::string> Container::getAccepts() { return accepts; }
std::vector<Item*> Container::getItem() { return items; }
std::vector<Trigger*> Container::getTrigger() { return triggers; }
