#ifndef XMLParser_H_
#define XMLParser_H_
#include <string>
#include <vector>
#include "map/Thing.h"
#include "map/Map.h"
#include "map/Room.h"
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"

class XMLParser {
private:
    std::vector<Item*> items;
    std::vector<Creature*> creatures;
    std::vector<Container*> containers;

public:
    Attack * parseAttack(TiXmlElement *);
    Border * parseBorder(TiXmlElement *);
    Container * parseContainer(TiXmlElement *);
    Condition * parseCondition(TiXmlElement *);
    Creature * parseCreature(TiXmlElement *);
    Item * parseItem(TiXmlElement *);
    Room * parseRoom(TiXmlElement *);
    Trigger * parseTrigger(TiXmlElement *);  
    Turnon * parseTurnon(TiXmlElement *);
    Map * parseMap(const char *);

    virtual void addItem(Item * item);
    virtual void addCreature(Creature * creature);
    virtual void addContainer(Container * container);
    virtual void printVectors();
};

#endif