#include "../../header/map/Border.h"
#include <iostream>
#include <string>

Border::Border() {}
Border::~Border() {}

void Border::setDirection(std::string _direction) { direction = _direction; }
void Border::display() { if(getName() != "") std::cout << "Border: " << getName() << " - " << getDirection() << std::endl; }

std::string Border::getDirection() { return direction; }
