#ifndef OWNERCONDITION_H
#define OWNERCONDITION_H

#include "Condition.h"

class OwnerCondition : public Condition {
private:
    bool has;
    std::string item;
    std::string owner;

public:
    OwnerCondition(bool _has, std::string _item, std::string _owner);
    bool conditionMet(bool _has, std::string _item, std::string _owner);
};

#endif
