#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <vector>
#include "Condition.h"

class Attack {
private:
    std::vector<Condition*> conditions;
    std::string print;
    std::vector<std::string> actions;

public:
    Attack();
    virtual void display();
    
    virtual void addCondition(Condition *);
    virtual void setPrint(std::string);
    virtual void addAction(std::string);

    virtual std::vector<Condition*> getCondition();
    virtual std::string getPrint();
    virtual std::vector<std::string> getActions();
};

#endif
