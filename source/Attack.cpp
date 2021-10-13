#include "../header/Attack.h"
#include <iostream>
#include <string>

Attack::Attack() {}

void Attack::display() { std::cout << "Attack: " << std::endl; }

void Attack::addCondition(Condition* _condition) { conditions.push_back(_condition); }
void Attack::addPrints(std::string _print) { prints.push_back(_print); }
void Attack::addAction(Action* _action) { actions.push_back(_action); }

std::vector<Condition*> Attack::getCondition() { return conditions; }
std::vector<std::string> Attack::getPrints() { return prints; }
std::vector<Action*> Attack::getActions() { return actions; }
