#include "../../header/map/Attack.h"
#include <iostream>
#include <string>

Attack::Attack() {}
Attack::~Attack() {}

void Attack::addCondition(Condition* _condition) { conditions.push_back(_condition); }
void Attack::setPrint(std::string _print) { print = _print; }
void Attack::addAction(std::string _action) { actions.push_back(_action); }

std::vector<Condition*> Attack::getCondition() { return conditions; }
std::string Attack::getPrint() { return print; }
std::vector<std::string> Attack::getActions() { return actions; }

void Attack::display() { if(getActions().size() != 0)  std::cout << "Attack: " <<  getPrint() << std::endl; }
