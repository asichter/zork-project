#include "../header/Trigger.h"
#include <iostream>
#include <string>

Trigger::Trigger() {}

void Trigger::display() {  std::cout << "Trigger: " << getName() << std::endl; }

void Trigger::setCommand(std::string _command) { command = _command; }
void Trigger::addCondition(Condition* _condition) { conditions.push_back(_condition); }
void Trigger::addPrints(std::string _print) { prints.push_back(_print); }
void Trigger::addAction(Action* _action) { actions.push_back(_action); }

std::string Trigger::getCommand() { return command; }
std::vector<Condition*> Trigger::getCondition() { return conditions; }
std::vector<std::string> Trigger::getPrints() { return prints; }
std::vector<Action*> Trigger::getActions() { return actions; }
