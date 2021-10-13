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
    
    virtual void addBorder(Border* _border);
    virtual void addItem(Item* _item);
    virtual void addContainer(Container* _container);
    virtual void addCreature(Creature* _creature);
    virtual void addTrigger(Trigger* _trigger);

    virtual std::vector<Border*> getBorder();
    virtual std::vector<Item*> getItem();
    virtual std::vector<Container*> getContainer();
    virtual std::vector<Creature*> getCreature();
    virtual std::vector<Trigger*> getTrigger();
};

#endif
