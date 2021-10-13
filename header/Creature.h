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
    Creature();
    virtual void display();
    
    virtual void addVulnerability(std::string _vulnerability);
    virtual void setAttack(Attack* _attack);
    virtual void addTrigger(Trigger* _trigger);

    virtual std::vector<std::string> getVulnerability();
    virtual Attack* getAttack();
    virtual std::vector<Trigger*> getTrigger();
};

#endif
