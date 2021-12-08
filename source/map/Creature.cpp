#include "../../header/map/Creature.h"
#include <iostream>
#include <string>

Creature::Creature() {}
Creature::~Creature() {}

void Creature::display() { if(getName() != "") std::cout << "Creature: " << getName() << std::endl; }

void Creature::printAttrs()
{
    std::cout << "Creature: " << getName() << std::endl;
    std::cout << "  Status: " << getStatus() << std::endl;
    std::cout << "  Deleted?: " << getDeleted() << std::endl;
    std::cout << "  Attack: " << getAttack() << std::endl;
    std::cout << "  Triggers: " << std::endl;
    for (Trigger* t : triggers)
    {
        std::cout << "    ";
        t->display(); 
    }
    std::cout << "  Vulnerabilities: " << std::endl;
    for (std::string v : vulnerabilities)
        std::cout << "    " << v << std::endl; 
}

void Creature::addVulnerability(std::string _vulnerability) { vulnerabilities.push_back(_vulnerability); }
void Creature::addAttack(Attack* _attack) { attack = _attack; }
void Creature::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::vector<std::string> Creature::getVulnerabilities() { return vulnerabilities; }
Attack * Creature::getAttack() { return attack; }
std::vector<Trigger*> Creature::getTriggers() { return triggers; }
