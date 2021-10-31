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

void StatusCondition::display() { std::cout << "Condition: " << getType() << std::endl; }
