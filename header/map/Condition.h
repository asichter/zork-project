#ifndef CONDITION_H
#define CONDITION_H

#include <string>

class Condition {
protected:
    std::string type;

public:
    Condition();
    ~Condition();
    virtual std::string getType();
    virtual void display();
    virtual void printAttrs();
};

#endif
