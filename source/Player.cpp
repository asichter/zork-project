#include "../header/Player.h"
#include <string>
#include <iostream>
#include <vector>

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
    currentRoom->removeItem(item);
    std::cout << "Added the " << item->getName() << " to the inventory." << std::endl;
}

bool Player::atExit() {
    if (currentRoom->getType() == "exit"){
        return true;
    }
    return false;
}

void Player::drop(Item * item) {
    int index = 0;
    for (Item * i : inventory) {
        if (i->getName() == item->getName()) {
            currentRoom->addItem(i);
            inventory.erase(inventory.begin() + index);
            std::cout << "Dropped the " << i->getName() << "." << std::endl;
        }
        index++;
    }
}

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
