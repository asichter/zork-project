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
    Player(Map* map);
    virtual void move(std::string dir, Map* map);
    virtual void printInventory();
    virtual void take(Item * item);
    virtual bool atExit();
    virtual void drop(Item * item);

    std::vector<Item*> getInventory();
    void printCurrentRoom();
    Room* getCurrentRoom();
    std::string getCurrentRoomName();
};

#endif
