#include "../../header/map/StatusCondition.h"
#include <iostream>
#include <string>

StatusCondition::StatusCondition(std::string _object, std::string _status) {
    type = "status";
    object = _object;
    status = _status;
}

bool StatusCondition::conditionMet(std::string _object, std::string _status) {
    if(_object != object || _status != status) {
        return false;
    }

    return true;
}

std::string StatusCondition::getObject() { return object; }
std::string StatusCondition::getStatus() { return status; }

void StatusCondition::display() { std::cout << "Condition: " << getType() << std::endl; }

void StatusCondition::printAttrs() {
    std::cout << "type: " + getType() << std::endl;
    std::cout << "object: " + getObject() << std::endl;
    std::cout << "status: " + getStatus() << std::endl;
}
