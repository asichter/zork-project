#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>
#include <vector>
#include "Condition.h"
#include "OwnerCondition.h"
#include "StatusCondition.h"
#include "Action.h"

class Trigger {
private:
    std::string type;
    std::string command;
    std::vector<Condition*> conditions;
    std::vector<std::string> prints;
    std::vector<Action*> actions;

public:
    Trigger(std::string _type, std::string _command, std::vector<Condition*> _conditions, std::vector<std::string> _prints, std::vector<Action*> _actions);
};

#endif
