#include "../header/Item.h"
#include <iostream>
#include <string>

Item::Item() {
    name = "";
    status = "";
    description = "";
    writing = "";
    turnon = NULL;
}
Item::~Item() {}
void Item::display() { if(getName() != "") std::cout << "Item: " << getName() << std::endl; }
void Item::printAttrs()
{
    std::cout << "Item: " << getName() << std::endl;
    std::cout << "  Status: " << getStatus() << std::endl;
    std::cout << "  Description: " << getDescription() << std::endl;
    std::cout << "  Writing: " << getWriting() << std::endl;
    std::cout << "  Turnon: "  << std::endl;
    if (turnon != NULL)
        turnon->display();
    std::cout << "  Triggers: " << std::endl;
    for (Trigger* t : triggers)
    {
        std::cout << "    ";
        t->display(); 
    }
}

void Item::setWriting(std::string _writing) { writing = _writing; }
void Item::setTurnon(Turnon* _turnon) { turnon = _turnon; }
void Item::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::string Item::getWriting() { return writing; }
Turnon* Item::getTurnon() { return turnon; }
std::vector<Trigger*> Item::getTrigger() { return triggers; }
