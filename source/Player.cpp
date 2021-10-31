#include "../header/Player.h"
#include <string>
#include <iostream>
#include <vector>

void Player::Player() {
    currentRoom = rooms[0];
    inventory = NULL;
}

void Player::move(std::string dir) {
    // check borders of current room
    // if valid, move there,
    // else print "cannot move that way"
}

void Player::i() {
    std::cout << "Inventory:" << std::endl;
    for (Item * i : items) 
        std::cout << "   -" << i.getName() << std::endl;
}

void Player::take(Item * item) {
    inventory.push_back(item);
}

void Player::op