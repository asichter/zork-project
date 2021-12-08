#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Thing.h"
#include "Border.h"
#include "Creature.h"
#include "Container.h"
#include "Trigger.h"

class Room : public Thing {
private:
    std::string name;
    std::string status;
    std::string type;
    std::string description;
    std::vector<Border*> borders;
    std::vector<Item*> items;
    std::vector<Container*> containers;
    std::vector<Creature*> creatures;
    std::vector<Trigger*> triggers;

public:
    Room();
    virtual void display();
    virtual void printAttrs();
    
    virtual void addBorder(Border* _border);
    virtual void addItem(Item* _item);
    virtual void addContainer(Container* _container);
    virtual void addCreature(Creature* _creature);
    virtual void addTrigger(Trigger* _trigger);

    virtual void removeItem(Item* item);

    virtual std::vector<Border*> getBorders();
    virtual std::vector<Item*> getItems();
    virtual std::vector<Container*> getContainers();
    virtual std::vector<Creature*> getCreatures();
    virtual std::vector<Trigger*> getTriggers();

    virtual Trigger * hasTrigger(std::string cmd);

    virtual void printItems();
    virtual void printCreatures();
    virtual void printContainers();
    virtual void printTriggers();
    virtual void printBorders();

    virtual void printRoom();
};

#endif
