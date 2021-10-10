#ifndef STATUSCONDITION_H
#define STATUSCONDITION_H

#include "Condition.h"

class StatusCondition : public Condition {
private:
    std::string item;
    std::string status;

public:
    StatusCondition(std::string _item, std::string _status);
    bool conditionMet(std::string _item, std::string _status);
};

#endif
