#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <vector>
#include "Condition.h"

class Attack {
private:
    std::vector<Condition*> conditions;
    std::vector<std::string> prints;
    std::vector<std::string> actions;

public:
    Attack();
    ~Attack();
    
    virtual void display();
    
    virtual void addCondition(Condition *);
    virtual void addPrint(std::string);
    virtual void addAction(std::string);

    virtual std::vector<Condition*> getConditions();
    virtual std::vector<std::string> getPrints();
    virtual std::vector<std::string> getActions();
};

#endif
