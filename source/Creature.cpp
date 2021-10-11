#include "../header/Creature.h"

Creature::Creature(std::string _name, std::vector<std::string> _vulnerabilities, Attack* _attack, std::vector<Trigger*> _triggers) {
    name = _name;
    vulnerabilities = _vulnerabilities;
    attack = _attack;
    triggers = _triggers;
}
