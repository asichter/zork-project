#include "../header/StatusCondition.h"

StatusCondition::StatusCondition(std::string _item, std::string _status) {
    type = "status";
    item = _item;
    status = _status;
}

bool StatusCondition::conditionMet(std::string _item, std::string _status) {
    if(_item != item || _status != status) {
        return false;
    }

    return true;
}
