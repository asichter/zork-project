#ifndef CONDITION_H
#define CONDITION_H

#include <string>

class Condition {
protected:
    std::string type;

public:
    Condition();
    virtual std::string getType();
    virtual bool conditionMet( ) = 0;
};

#endif
