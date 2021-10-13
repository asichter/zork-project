#include "../header/Condition.h"
#include <iostream>
#include <string>

Condition::Condition() { }

std::string Condition::getType() {
    return type;
}

void Condition::display() { std::cout << "Condition: " << std::endl; }
