#include "../header/Item.h"
#include <iostream>
#include <string>

Item::Item() {}
void Item::display() { std::cout << "Item: " << getName() << std::endl; }