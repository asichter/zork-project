#include "../header/Thing.h"
#include <iostream>
#include <string>

void Thing::setName(std::string _name) { name = _name; }
void Thing::setDescription(std::string _description) { description = _description; }
void Thing::setStatus(std::string _status) { status = _status; }
void Thing::setType(std::string _type) { type = _type; }

std::string Thing::getName() { return name; }
std::string Thing::getDescription() { return description; }
std::string Thing::getStatus() { return status; }
std::string Thing::getType() { return type; }
