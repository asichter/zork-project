#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>
#include <vector>
#include "Condition.h"
#include "OwnerCondition.h"
#include "StatusCondition.h"
#include "Thing.h"

class Trigger : public Thing {
private:
    std::string type;
    std::string command;
    std::vector<Condition*> conditions;
    std::vector<std::string> prints;
    std::vector<std::string> actions;

public:
    Trigger();
    virtual void display();
    
    virtual void setCommand(std::string _command);
    virtual void addCondition(Condition* _condition);
    virtual void addPrints(std::string _print);
    virtual void addAction(std::string _action);

    virtual void printAttrs();

    virtual std::string getCommand();
    virtual std::vector<Condition*> getConditions();
    virtual std::vector<std::string> getPrints();
    virtual std::vector<std::string> getActions();
};

#endif
