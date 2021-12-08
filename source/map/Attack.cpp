#include "../../header/map/Attack.h"
#include <iostream>
#include <string>

Attack::Attack() {}
Attack::~Attack() {}

void Attack::addCondition(Condition* _condition) { conditions.push_back(_condition); }
void Attack::addPrint(std::string _print) { prints.push_back(_print); }
void Attack::addAction(std::string _action) { actions.push_back(_action); }

std::vector<Condition*> Attack::getConditions() { return conditions; }
std::vector<std::string> Attack::getPrints() { return prints; }
std::vector<std::string> Attack::getActions() { return actions; }

void Attack::display() { if(getActions().size() != 0)  std::cout << "Attack: " <<  getPrints().front() << std::endl; }
