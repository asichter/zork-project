#ifndef Player_H_
#define Player_H_
#include <string>
#include <vector>
#include "map/Map.h"

class Player {
private:
    std::vector<Item*> inventory;
    Room * currentRoom;
    friend class Map;

public:
    virtual void move(std::string dir);
    virtual void i();
    virtual void take(Item * item);
    virtual bool open_exit();
    virtual void drop(Item * item);

    std::vector<Item*> getInventory();
    Room * getRoom();
}