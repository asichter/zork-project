#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include "Attack.h"
#include "Trigger.h"

class Creature {
private:
    std::string name;
    std::vector<std::string> vulnerabilities;
    Attack* attack;
    std::vector<Trigger*> triggers;

public:
    Creature(std::string _name, std::vector<std::string> _vulnerabilities, Attack* _attack, std::vector<Trigger*> _triggers);
};

#endif
