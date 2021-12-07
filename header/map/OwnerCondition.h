#ifndef OWNERCONDITION_H
#define OWNERCONDITION_H

#include "Condition.h"

class OwnerCondition : public Condition {
private:
    bool has;
    std::string object;
    std::string owner;

public:
    OwnerCondition(bool _has, std::string _object, std::string _owner);
    bool conditionMet(bool _has, std::string _object, std::string _owner);

    virtual bool getHas();
    virtual std::string getObject();
    virtual std::string getOwner();

    void display();
    virtual void printAttrs();
};

#endif
