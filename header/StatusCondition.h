#ifndef STATUSCONDITION_H
#define STATUSCONDITION_H

#include "Condition.h"

class StatusCondition : public Condition {
private:
    std::string object;
    std::string status;

public:
    StatusCondition(std::string _object, std::string _status);
    bool conditionMet(std::string _object, std::string _status);
    void display();
};

#endif
