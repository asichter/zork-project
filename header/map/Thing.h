#ifndef THING_H
#define THING_H

#include <string>
#include <vector>

class Thing {
protected:
    std::string name;
    std::string description;
    std::string status;
    std::string type;

public:
    virtual void display() = 0;
    virtual void setName(std::string _name);
    virtual void setDescription(std::string _description);
    virtual void setStatus(std::string _status);
    virtual void setType(std::string _type);

    virtual std::string getName();
    virtual std::string getDescription();
    virtual std::string getStatus();
    virtual std::string getType();
};

#endif
