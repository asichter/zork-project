#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include "Attack.h"
#include "Trigger.h"
#include "Thing.h"

class Creature : public Thing {
private:
    std::string name;
    std::string status;
    std::vector<std::string> vulnerabilities;
    Attack* attack;
    std::vector<Trigger*> triggers;

public:
    Creature();
    ~Creature();
    virtual void display();
    
    virtual void addVulnerability(std::string _vulnerability);
    virtual void addAttack(Attack* _attack);
    virtual void addTrigger(Trigger* _trigger);

    virtual std::vector<std::string> getVulnerability();
    virtual Attack* getAttack();
    virtual std::vector<Trigger*> getTrigger();
};

#endif
