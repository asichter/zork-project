#include "../header/Container.h"
#include <iostream>
#include <string>

Container::Container() {}
Container::~Container() {}

void Container::display() { 
    if(getName() != "") std::cout << "Container: " << getName() << std::endl; 
    std::cout << "no. if items: " << items.size() << std::endl;
    for (Item* i : items)
        i->display();
}

void Container::printAttrs() { 
    if(getName() != "") std::cout << "Container: " << getName() << std::endl; 
    std::cout << status << std::endl;
    std::cout << description << std::endl;
    for (std::string a : accepts)
        std::cout << a << std::endl;
    for (Trigger* t : triggers)
        t->display();
    for (Item* i : items)
        i->printAttrs();
}

void Container::addAccepts(std::string _accept) {accepts.push_back(_accept); }
void Container::addItem(Item* _item) { items.push_back(_item); }
void Container::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }
void Container::setName(std::string _name) { name = _name; }

std::vector<std::string> Container::getAccepts() { return accepts; }
std::vector<Item*> Container::getItem() { return items; }
std::vector<Trigger*> Container::getTrigger() { return triggers; }
std::string Container::getName() { return name; }
