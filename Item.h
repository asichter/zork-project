#ifndef ITEM_H
#define ITEM_G

#include "Trigger.h"

class Item {
private:
    std::string name;
    std::string status;
    std::string description;
    std::string writing;
    std::string turnon;
    std::vector<Trigger*> triggers;

public:
    Item(std::string _name, std::string _status, std::string _description, std::string _writing, std::string _turnon, std::vector<Trigger*> _triggers);
}

#endif
