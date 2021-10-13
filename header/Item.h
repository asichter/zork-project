#ifndef ITEM_H_
#define ITEM_H_

#include "Trigger.h"
#include "Turnon.h"
#include "Thing.h"

class Item : public Thing {
private:
    std::string name;
    std::string status;
    std::string description;
    std::string writing;
    Turnon* turnon;
    std::vector<Trigger*> triggers;

public:
    Item();
    virtual void display();

    virtual void setWriting(std::string _writing);
    virtual void setTurnon(Turnon* _turnon);
    virtual void addTrigger(Trigger* _trigger);

    virtual std::string getWriting();
    virtual Turnon* getTurnon();
    virtual std::vector<Trigger*> getTrigger();
};

#endif
