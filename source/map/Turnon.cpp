#include "../../header/map/Turnon.h"
#include <iostream>
#include <string>

Turnon::Turnon() {}

void Turnon::setPrint(std::string _print) { print = _print; }
void Turnon::addAction(std::string _action) { actions.push_back(_action); }

std::string Turnon::getPrint() { return print; }
std::vector<std::string> Turnon::getActions() { return actions; }

void Turnon::display() { std::cout << "Turnon: found " << getActions().size() << " actions" << std::endl; }
