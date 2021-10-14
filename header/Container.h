#ifndef CONTAINER_H
#define CONTAINER_H

#include <string>
#include <vector>
#include "Item.h"
#include "Thing.h"

class Container : public Thing {
private:
    std::string name;
    std::string status;
    std::string description;
    std::vector<std::string> accepts;
    std::vector<Trigger*> triggers;
    std::vector<Item*> items;

public:
    Container();
    ~Container(); 
    virtual void display();
    virtual void addAccepts(std::string _accept);
    virtual void addItem(Item* _item);
    virtual void addTrigger(Trigger* _trigger);
    virtual void setName(std::string _name);

    virtual std::vector<std::string> getAccepts();
    virtual std::vector<Trigger*> getTrigger();
    virtual std::vector<Item*> getItem();
    std::string getName();
};

#endif
