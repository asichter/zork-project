#include "../../header/map/Item.h"
#include <iostream>
#include <string>
#include <sstream>

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
    std::cout << "  Deleted?: " << getDeleted() << std::endl;
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

void Item::turn_on() {
    std::vector<std::string> action_vec;
    std::string turnon_action = turnon->getActions().front();
    transform(turnon_action.begin(), turnon_action.end(), turnon_action.begin(), ::tolower);
    std::istringstream ss(turnon_action);
    std::string word;
    while (ss >> word) { action_vec.push_back(word); }

    std::string print_str = turnon->getPrint();
    this->setStatus(action_vec.at(1));
    std::cout << "\t" + print_str << std::endl;
}
