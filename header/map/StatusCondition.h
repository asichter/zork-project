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

    virtual std::string getObject();
    virtual std::string getStatus();

    void display();
    virtual void printAttrs();
};

#endif
