#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <vector>
#include "Condition.h"
#include "Action.h"

class Attack {
private:
    std::vector<Condition*> conditions;
    std::vector<std::string> prints;
    std::vector<Action*> actions;

public:
    Attack();
    virtual void display();
    
    virtual void addCondition(Condition *);
    virtual void addPrints(std::string);
    virtual void addAction(Action*);

    virtual std::vector<Condition*> getCondition();
    virtual std::vector<std::string> getPrints();
    virtual std::vector<Action*> getActions();
};

#endif
