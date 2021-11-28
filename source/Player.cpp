#include "../header/Player.h"
#include <string>
#include <iostream>
#include <vector>

template <typename T>
T contains(std::vector<T> vec, const T & elem){
    for (auto * a : vec) {
        if (a == elem)
            return a;
    }
    return NULL;
}
template <typename T>
T contains(std::vector<T> vec, const std::string name) {
    for (auto * e : vec) {
        if (e->getName() == name)
            return e;
    }
    return NULL;
}

Player::Player(Map* map) {
    std::vector<Room*> rooms = map->getRooms();
    currentRoom = NULL;
    for(Room* r : rooms) {
        if(r->getName() == "Entrance" || r->getName() == "entrance") {
            currentRoom = r;
        }
    }
    if(currentRoom == NULL) {
        currentRoom = rooms[0];
    }
    inventory = std::vector<Item*>();
}

void Player::move(std::string dir, Map* map) {
    // check borders of current room
    // if valid, move there,
    // else print "cannot move that way"
    std::vector<Border*> borders = currentRoom->getBorder();
    std::vector<Room*> rooms = map->getRooms();
    std::string nextRoom = "none";

    if(dir == "n" || dir == "north") {
        for(Border* b : borders) {
            if(b->getDirection() == "north") {
                nextRoom = b->getName();
            }
        }
    }
    else if(dir == "s" || dir == "south") {
        for(Border* b : borders) {
            if(b->getDirection() == "south") {
                nextRoom = b->getName();
            }
        }
    }
    else if(dir == "e" || dir == "east") {
        for(Border* b : borders) {
            if(b->getDirection() == "east") {
                nextRoom = b->getName();
            }
        }
    }
    else if(dir == "w" || dir == "west") {
        for(Border* b : borders) {
            if(b->getDirection() == "west") {
                nextRoom = b->getName();
            }
        }
    }

    if(nextRoom == "none") {
        std::cout << "Cannot move that way..." << std::endl;
    }
    else {
        for (Room* r : rooms) {
            if(r->getName() == nextRoom) {
                currentRoom = r;
            }
        }
        std::cout << "Moved into " << currentRoom->getName() << std::endl;
        std::cout << currentRoom->getDescription() << std::endl;
    }
}

void Player::remove(Item * item) {
    int index = 0;
    for (Item * i : inventory) {
        if (i->getName() == item->getName()) {
            inventory.erase(inventory.begin() + index);
        }
        index++;
    }
}

void Player::printInventory() {
    std::cout << "Inventory:" << std::endl;
    if(inventory.size() != 0) {
        for (Item * i : inventory) 
            std::cout << "   -" << i->getName() << std::endl;
    }
    else {
        std::cout << "Empty." << std::endl;
    }
}

void Player::take(Item * item) {
    inventory.push_back(item);
    if (contains(currentRoom->getItem(), item))
        currentRoom->removeItem(item);
    else  {
        std::vector<Container*> cs = currentRoom->getContainer();
        for (auto c : cs) {
            if(contains(c->getItem(), item))
                c->removeItem(item);
        }
    }
    std::cout << "\tAdded the " << item->getName() << " to the inventory." << std::endl;
}

bool Player::atExit() {
    if (currentRoom->getType() == "exit"){
        return true;
    }
    return false;
}

void Player::drop(Item * item) {
    remove(item);
    currentRoom->addItem(item);
    std::cout << "\tDropped the " << item->getName() << "." << std::endl;
}

void Player::open(Container * container) { 
    container->open();
}

void Player::read(Item * item, std::string name) { 
    if (item == NULL)
        std::cout << "\t" + name + " not in inventory." << std::endl;
    else {
        std::string writing = item->getWriting();
        if(writing != "")
            std::cout << "\t" + item->getWriting() << std::endl;
        else
            std::cout << "\tNothing written" << std::endl;
    }
}

void Player::put(Item * item, Container * container) { 
    remove(item);
    container->addItem(item);

}

void Player::turn_on(Item * item) { }

void Player::attack(Creature * creature, Item * item) { }

std::vector<Item*> Player::getInventory() {
    return inventory;
}

void Player::printCurrentRoom() {
    std::cout << currentRoom->getName() << std::endl;
}

Room* Player::getCurrentRoom() {
    return currentRoom;
}

std::string Player::getCurrentRoomName() {
    return currentRoom->getName();
}

bool Player::inInventory(Item * item) {
    for (Item * i : inventory) {
        if (item == i)
            return 1;
    }
    return 0;
}
