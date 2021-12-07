#include "../../header/map/Condition.h"
#include <iostream>
#include <string>

Condition::Condition() {}
Condition::~Condition() {}

std::string Condition::getType() { return type; }
void Condition::display() { if(getType() != "") std::cout << "Condition: " << getType() << std::endl; }
void Condition::printAttrs() { display(); }