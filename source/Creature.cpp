#include "../header/Creature.h"
#include <iostream>
#include <string>

Creature::Creature() {}

void Creature::display() { std::cout << "Creature: " << getName() << std::endl; }

void Creature::addVulnerability(std::string _vulnerability) { vulnerabilities.push_back(_vulnerability); }
void Creature::setAttack(Attack* _attack) { attack = _attack; }
void Creature::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

std::vector<std::string> getVulnerability() { return vulnerabilities; }
Attack * getAttack() { return attack; }
std::vector<Trigger*> getTrigger() { return triggers; }
