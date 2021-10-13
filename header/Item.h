#ifndef ITEM_H
#define ITEM_G

#include "Trigger.h"
#include "Thing.h"

class Item : public Thing {
private:
    std::string name;
    std::string status;
    std::string description;
    std::string writing;
    std::string turnon;
    std::vector<Trigger*> triggers;

public:
    Item();
    virtual void display();
};

#endif
