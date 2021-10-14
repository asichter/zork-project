#include "../header/Item.h"
#include <iostream>
#include <string>

Item::Item() {}
Item::~Item() {}
void Item::display() { std::cout << "Item: " << getName() << std::endl; }

void Item::setWriting(std::string _writing) { writing = _writing; }
void Item::setTurnon(Turnon* _turnon) { turnon = _turnon; }
void Item::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::string Item::getWriting() { return writing; }
Turnon* Item::getTurnon() { return turnon; }
std::vector<Trigger*> Item::getTrigger() { return triggers; }
