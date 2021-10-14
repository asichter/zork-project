#ifndef TURNON_H
#define TURNON_H

#include <string>
#include <vector>
#include <iostream>
#include "Thing.h"

class Turnon : public Thing {
private:
    std::string print;
    std::vector<std::string> actions;

public:
    Turnon();
    
    virtual void setPrint(std::string _print);
    virtual void addAction(std::string _action);
    void display();

    std::string getPrint();
    std::vector<std::string> getAction();
};

#endif