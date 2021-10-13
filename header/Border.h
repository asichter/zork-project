#ifndef Border_H_
#define Border_H_

#include <string>
#include "../header/Thing.h"

class Border : public Thing {
private:
    std::string name;
    std::string direction;

public:
    Border();
    virtual void setDirection(std::string _direction);
    virtual void display();
};

#endif