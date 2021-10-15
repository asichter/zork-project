#ifndef XMLParser_H_
#define XMLParser_H_
#include <string>
#include "Thing.h"
#include "Map.h"
#include "Room.h"
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"

class XMLParser {
private:

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
    void parseMap(const char *);
};

#endif