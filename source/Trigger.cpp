#include "../header/Trigger.h"

Trigger::Trigger(std::string _type, std::string _command, std::vector<Condition*> _conditions, std::vector<std::string> _prints, std::vector<Action*> _actions) {
    type = _type;
    conditions = _conditions;
    prints = _prints;
    actions = _actions;
}
