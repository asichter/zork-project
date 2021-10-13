#ifndef XMLParser_H_
#define XMLParser_H_
#include <string>
#include "Thing.h"
#include "Map.h"
#include "Room.h"
#include "../tinyxml/tinyxml.h"
#include "../tinyxml/tinystr.h"

Border * parseBorder(TiXmlElement *);
Container * parseContainer(TiXmlElement *);
Item * parseItem(TiXmlElement *);
Room * parseRoom(TiXmlElement *);
Trigger * parseTrigger(TiXmlElement *);  
void parseMap(const char *);

#endif