#include "../header/Creature.h"
#include <iostream>
#include <string>

Creature::Creature() {}
Creature::~Creature() {}

void Creature::display() { if(getName() != "") std::cout << "Creature: " << getName() << std::endl; }

void Creature::addVulnerability(std::string _vulnerability) { vulnerabilities.push_back(_vulnerability); }
void Creature::addAttack(Attack* _attack) { attack = _attack; }
void Creature::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::vector<std::string> Creature::getVulnerability() { return vulnerabilities; }
Attack * Creature::getAttack() { return attack; }
std::vector<Trigger*> Creature::getTrigger() { return triggers; }
