#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>
#include "Item.h"
#include "Trigger.h"

class Container {
private:
    std::string name;
    std::string status;
    std::string description;
    std::vector<std::string> accepts;
    std::vector<Trigger*> triggers;
    std::vector<Item*> items;

public:
    Container(std::string _name, std::string _status, std::string _description, std::vector<std::string> _accepts, std::vector<Trigger*> _triggers, std::vector<Item*> _items);
};

#endif
