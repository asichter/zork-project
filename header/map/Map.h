#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "Thing.h"
#include "Room.h"

class Map : public Thing {
private:
    std::string name;
    std::string description;
    // Border* border;
    std::vector<Room*> rooms;
    std::vector<Item*> items;
    std::vector<Creature*> creatures;
    std::vector<Container*> containers;
    std::vector<Trigger*> triggers;

public:
    Map();
    void display();
    
    virtual void addRoom(Room * _room);
    virtual void addItem(Item * _item);
    virtual void addCreature(Creature * _creature);
    virtual void addContainer(Container* _container);
    virtual void addTrigger(Trigger * _trigger);

    virtual std::vector<Room*> getRooms();
    virtual std::vector<Item*> getItems();
    virtual std::vector<Creature*> getCreatures();
    virtual std::vector<Container*> getContainers();
    virtual std::vector<Trigger*> getTriggers();

    virtual void printRooms();
    virtual void printItems();
    virtual void printVectors();
    virtual void printEVERYTHING();
};

#endif
