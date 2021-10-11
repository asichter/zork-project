#include "tinyxml/tinyxml.h"
#include "XMLParser.h"
#include <string>
#include <iostream>

Action * parseAction(TiXmlElement * element) 
{
  Action * action = new Action();
  for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
    TiXmlElement * childElement = node->ToElement();
    if (childElement != NULL) 
    {
      std::string name = childElement->ValueStr();
      std::string value = childElement->GetText();
      if (name=="item")
        action->setItem(value);
      else if (name=="container")
        action->setContainer(value);
      else if (name=="status")
        action->setStatus(value);
      else if (name=="target")
        action->setTarget(value);
    }
  }
  return action;
}

Attack * parseAttack(TiXmlElement * element) {}

Condition * parseCondition(TiXmlElement * element) 
{
  Condition * condition = new Condition();
  for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
    TiXmlElement * childElement = node->ToElement();
    if (childElement != NULL) 
    {
      std::string name = childElement->ValueStr();
      std::string value = childElement->GetText();
      if (name=="")
    }
  }
  return action;
}
Container * parseConatiner(TiXmlElement * element) {}
Creature * parseCreature(TiXmlElement * element) {}
Item * parseItem(TiXmlElement * element) {}
Map * parseMap(TiXmlElement * element) {}
OwnerCondition * parseOwnerCondition(TiXmlElement * element) {}
Room * parseRoom(TiXmlElement * element) {}
StatusCondition * parseStatusCondition(TiXmlElement * element) {}
Trigger * parseTrigger(TiXmlElement * element) {}

void XMLParser::parseData(const char * filename) {
  TiXmlDocument doc(filename);
  doc.LoadFile();

  // fetch root elem
  TiXmlElement * rootElement = doc.RootElement();
  if (rootElement != NULL && rootElement->ValueTStr() == "map") 
  {
    for (TiXmlNode* node = rootElement->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
      TiXmlElement * childElement = node->ToElement();
      if (childElement != NULL)
      {
        std::string name = childElement->ValueStr();
        if (name == "room")
        else if (name == "item")
        else if (name == "creature")
        else if (name == "container")
        
      }
    }
  }
}
