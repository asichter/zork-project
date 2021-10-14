#include "../header/Trigger.h"
#include <iostream>
#include <string>

Trigger::Trigger() {}

void Trigger::display() {  if(getActions().size() != 0) std::cout << "Trigger: found trigger with " << getActions().size() << " action(s)" << std::endl; }

void Trigger::setCommand(std::string _command) { command = _command; }
void Trigger::addCondition(Condition* _condition) { conditions.push_back(_condition); }
void Trigger::addPrints(std::string _print) { prints.push_back(_print); }
void Trigger::addAction(std::string _action) { actions.push_back(_action); }

std::string Trigger::getCommand() { return command; }
std::vector<Condition*> Trigger::getCondition() { return conditions; }
std::vector<std::string> Trigger::getPrints() { return prints; }
std::vector<std::string> Trigger::getActions() { return actions; }

