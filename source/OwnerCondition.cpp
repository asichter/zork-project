#include "OwnerCondition.h"

OwnerCondition::OwnerCondition(bool _has, std::string _item, std::string _owner) {
    type = "owner";
    has = _has;
    item = _item;
    owner = _owner;
}

bool OwnerCondition::conditionMet(bool _has, std::string _item, std::string _owner) {
    if(_has != has || _item != item || _owner != owner) {
        return false;
    }

    return true;
}
