#include "../header/Condition.h"
#include <iostream>
#include <string>

Condition::Condition() {}
Condition::~Condition() {}

std::string Condition::getType() { return type; }
void Condition::display() { std::cout << "Condition: " << getType() << std::endl; }
