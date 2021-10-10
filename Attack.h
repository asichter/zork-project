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
    Attack(std::vector<Condition*> _conditions, std::vector<std::string> _prints, std::vector<Action*> _actions);
};

#endif
