#include "../header/Map.h"

Map::Map(std::vector<Room*> _rooms, std::vector<Item*> _items, std::vector<Creature*> _creatures, std::vector<Container*> _containers) {
    rooms = _rooms;
    items = _items;
    creatures = _creatures;
    containers = _containers;
}
