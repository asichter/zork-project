#include "../header/Border.h"
#include <iostream>
#include <string>

Border::Border() {}
Border::~Border() {}

void Border::setDirection(std::string _direction) { direction = _direction; }
void Border::display() { std::cout << "Border: " << getName() << " - " << getDirection() << std::endl; }

std::string Border::getDirection() { return direction; }
