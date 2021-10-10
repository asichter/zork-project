#ifndef ACTION_H
#define ACTION_H

#include <string>

class Action {
protected:
    std::string type;
    std::string item;
    std::string container;
    std::string status;
    std::string target;

public:
    Action(std::string _type);

    virtual void setItem(std::string _item);
    virtual void setContainter(std::string _container);
    virtual void setStatus(std::string _status);
    virtual void setTarget(std::string _target);

    virtual std::string getType();
    virtual std::string getItem();
    virtual std::string getContainer();
    virtual std::string getStatus();
    virtual std::string getTarget();
};

#endif
