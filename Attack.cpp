#include "Attack.h"

Attack::Attack(std::vector<Condition*> _conditions, std::vector<std::string> _prints, std::vector<Action*> _actions) {
    conditions = _conditions;
    prints = _prints;
    _actions = _actions;
}
