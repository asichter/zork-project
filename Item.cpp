#include "Item.h"


Item::Item(std::string _name, std::string _status, std::string _description, std::string _writing, std::string _turnon, std::vector<Trigger*> _triggers) {
    name = _name;
    status = _status;
    description = _description;
    writing = _writing;
    turnon = _turnon;
    triggers = _triggers;
}
