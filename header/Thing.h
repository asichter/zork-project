#ifndef THING_H
#define THING_H

#include <string>
#include <vector>

class Thing {
protected:
    std::string name;
    std::string description;
    std::string status;
    // std::string target;
    std::string type;
    
    // std::vector<Attack*> attacks;
    // std::vector<Condition*> conditions;
    // std::vector<Container*> containers;
    // std::vector<Creature*> creatures;
    // std::vector<Item*> items;
    // std::vector<
    // std::vector<Room*> rooms;
    // std::vector<Trigger*> triggers;
    // std::vector<std::string> vulnerabilities;

    // Border* border;

public:
    virtual void display() = 0;
    virtual void setName(std::string _name);
    virtual void setDescription(std::string _description);
    virtual void setStatus(std::string _status);
    virtual void setType(std::string _type);
    // virtual void addBorder(Border* _border);
    // virtual void addContainer(Container* _container);
    // virtual void addCreature(Creature* _creature);
    // virtual void addItem(Item* _item);
    // virtual void addTrigger(Trigger* _trigger);

    virtual std::string getName();
    virtual std::string getDescription();
    virtual std::string getStatus();
    virtual std::string getType();
};

#endif
