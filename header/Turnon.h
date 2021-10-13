#ifndef TURNON_H
#define TURNON_H

#include <string>
#include <vector>
#include <iostream>

class Turnon {
private:
    std::string print;
    std::vector<std::string> actions;

public:
    Turnon();
    
    virtual void setPrint(std::string _print);
    virtual void addAction(std::string _action);

    std::string getPrint();
    std::vector<std::string> getAction();
};

#endif