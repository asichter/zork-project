#include "Container.h"

Container::Container(std::string _name, std::string _status, std::string _description, std::vector<std::string> _accepts, std::vector<Trigger*> _triggers, std::vector<Item*> _items) {
    name = _name;
    status = _status;
    description = _description;
    accepts = _accepts;
    triggers = _triggers;
    items = _items;
}
