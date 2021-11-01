#include "../../header/map/Room.h"
#include <iostream>
#include <string>

Room::Room() {
    name = "";
    status = "";
    type = "regular";
    description = "";
}

void Room::display() 
{
    if(getName() != "") std::cout << "Room: " << this->getName() << std::endl;
}

void Room::printAttrs()
{
    std::cout << getName() << std::endl;
    std::cout << "  -Status: " << getStatus() << std::endl;
    std::cout << "  -Type  : " << getType() << std::endl;
    std::cout << "  -Descr : " << getDescription() << std::endl;
    for (Border* b : borders)
        b->display();
    for (Item * i : items)
        i->printAttrs();
    for (Container * c : containers)
        c->printAttrs();
    for (Creature * c : creatures)
        c->printAttrs();
    for (Trigger * t : triggers)
        t->display();
}

void Room::addBorder(Border* _border) { borders.push_back(_border); }
void Room::addItem(Item* _item) { items.push_back(_item); }
void Room::addContainer(Container* _container) { containers.push_back(_container); }
void Room::addCreature(Creature* _creature) { creatures.push_back(_creature); }
void Room::addTrigger(Trigger* _trigger) { triggers.push_back(_trigger); }

void Room::removeItem(Item* item) {
    int index = 0;
    for(Item* i : items) {
        if(i->getName() == item->getName()) {
            items.erase(items.begin() + index);
        }
        index++;
    }

    for(Container* c : containers) {
        c->removeItem(item);
    }
}

std::vector<Border*> Room::getBorder() { return borders; }
std::vector<Item*> Room::getItem() { return items; }
std::vector<Container*> Room::getContainer() { return containers; }
std::vector<Creature*> Room::getCreature() { return creatures; }
std::vector<Trigger*> Room::getTrigger() { return triggers; }

void Room::printItems() {
    std::cout << "no. if items: " << items.size() << std::endl;
    for(unsigned int i = 0; i < items.size(); i++) {
        items[i]->display();
    }
}

void Room::printCreatures() {
    std::cout << "no. if creatures: " << creatures.size() << std::endl;
    for(unsigned int i = 0; i < creatures.size(); i++) {
        creatures[i]->display();
    }
}

void Room::printContainers() {
    std::cout << "no. if containers: " << containers.size() << std::endl;
    for(unsigned int i = 0; i < containers.size(); i++) {
        containers[i]->display();
    }
}

void Room::printTriggers() {
    std::cout << "no. if triggers: " << triggers.size() << std::endl;
    for(unsigned int i = 0; i < triggers.size(); i++) {
        triggers[i]->display();
    }
}

void Room::printBorders() {
    for(unsigned int i = 0; i < borders.size(); i++) {
        borders[i]->display();
    }
}

void Room::printRoom() {
    display();
    printItems();
    printCreatures();
    printContainers();
    printBorders();
    printTriggers();
    std::cout << "end of room\n" << std::endl;
}
