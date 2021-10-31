#include "../../header/map/OwnerCondition.h"
#include <iostream>
#include <string>

OwnerCondition::OwnerCondition(bool _has, std::string _object, std::string _owner) {
    type = "owner";
    has = _has;
    object = _object;
    owner = _owner;
}

bool OwnerCondition::conditionMet(bool _has, std::string _object, std::string _owner) {
    if(_has != has || _object != object || _owner != owner) {
        return false;
    }

    return true;
}

void OwnerCondition::display() { std::cout << "Condition" << getType() << std::endl;}
