#include "../../header/map/Trigger.h"
#include <iostream>
#include <string>

Trigger::Trigger() {}

void Trigger::display() {  if(getActions().size() != 0) std::cout << "Trigger: found trigger with " << getActions().size() << " action(s)" << std::endl; }

void Trigger::setCommand(std::string _command) { command = _command; }
void Trigger::addCondition(Condition* _condition) { conditions.push_back(_condition); }
void Trigger::addPrints(std::string _print) { prints.push_back(_print); }
void Trigger::addAction(std::string _action) { actions.push_back(_action); }
void Trigger::printAttrs(){
    std::cout << "\tType: " + getType() << std::endl;
    std::cout << "\tDeleted?: " << getDeleted() << std::endl;
    std::cout << "\tCommand: " + getCommand() << std::endl;
    std::cout << "\tCondition: " << std::endl;
    for (Condition * c : getConditions()) {
        std::cout << "\t\t";
        c->display();
    }
    std::cout << "\tPrints: " << std::endl;
    for (std::string p : getPrints()) {
        std::cout << "\t\t" + p << std::endl;
    }
    std::cout << "\tActions: " << std::endl;
    for (std::string a : getActions()) {
        std::cout << "\t\t" + a << std::endl;
    }
}

std::string Trigger::getCommand() { return command; }
std::vector<Condition*> Trigger::getConditions() { return conditions; }
std::vector<std::string> Trigger::getPrints() { return prints; }
std::vector<std::string> Trigger::getActions() { return actions; }

