#include "../../header/map/Container.h"
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
    std::cout << "  Deleted?: " << getDeleted() << std::endl;
    std::cout << "  Status: " + getStatus() << std::endl;
    std::cout << "  Description: " + getDescription() << std::endl;
    std::cout << "  Accepts: " << std::endl;
    for (std::string a : getAccepts())
        std::cout << a << std::endl;
    std::cout << "  Triggers: " << std::endl;
    for (Trigger* t : getTriggers())
        t->display();
    std::cout << "  Items: " << std::endl;
    for (Item* i : items)
        i->printAttrs();
}

void Container::addAccepts(std::string _accept) {accepts.push_back(_accept); }
void Container::addItem(Item* _item) { items.push_back(_item); }
void Container::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }
void Container::setName(std::string _name) { name = _name; }

void Container::removeItem(Item* item) {
    int index = 0;
    for(Item* i : items) {
        if(i->getName() == item->getName()) {
            items.erase(items.begin() + index);
        }
        index++;
    }
}

bool Container::isOpen() { return openStatus; }
void Container::open() { 
    openStatus = 1; 
    std::string printString = "";
    printString += getName();
    if (getItems().empty())
        printString += " is empty.";
    else {
        printString += " contains ";
        for (auto i : getItems())
            printString += i->getName() + ", ";
        printString.pop_back();
        printString.pop_back();
        printString += ".";
    }
    std::cout << printString << std::endl;
}
void Container::close() { openStatus = 0; }

std::vector<std::string> Container::getAccepts() { return accepts; }
std::vector<Item*> Container::getItems() { return items; }
std::vector<Trigger*> Container::getTriggers() { return triggers; }
std::string Container::getName() { return name; }
