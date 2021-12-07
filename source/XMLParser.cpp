#include "../header/XMLParser.h"
#include <string>
#include <iostream>
#include <vector>

void XMLParser::addItem(Item* item)
{
    // std::cout << "item added" << std::endl;
    items.push_back(item);
}


void XMLParser::addCreature(Creature * creature)
{
    creatures.push_back(creature);
}


void XMLParser::addContainer(Container * container)
{
    containers.push_back(container);
}


void XMLParser::printVectors()
{   
    std::cout << "\nItems: " << items.size() << std::endl;
    for (Item* i : items)
        i->printAttrs();
    std::cout << "\nCreatures: " << creatures.size() << std::endl;
    for (Creature* c : creatures)
        c->printAttrs();
    std::cout << "\nContainers: " << containers.size() << std::endl;
    for (Container* cn : containers)
        cn->display();
}


Attack * XMLParser::parseAttack(TiXmlElement * element) 
{
    Attack * attack = new Attack();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "action")
                attack->addAction(value);
            else if (name == "print")
                attack->setPrint(value); 
        }
    }
    // attack->display();
    return attack;
}


Border * XMLParser::parseBorder(TiXmlElement * element) 
{
    Border * border = new Border();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();
            
            if (name == "name")
                border->setName(value);
            else if (name == "direction")
                border->setDirection(value);
        }
    }
    // border->display();
    return border;   
}


Condition * XMLParser::parseCondition(TiXmlElement * element) 
{
    Condition * condition = new Condition();
    // OwnerCondition * ownercondition = NULL;
    // StatusCondition * statuscondition = NULL;
    std::string has = "";
    std::string object = "";
    std::string owner = "";
    std::string status = "";

    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "has")
                has = value;
            else if (name == "object")
                object = value;
            else if (name == "owner")
                owner = value;
            else if (name == "status")
                status = value;
        }
    }
    if (has != "")
        condition = new OwnerCondition((has == "y"), object, owner);
    else
        condition = new StatusCondition(object, status);

    // condition->display();
    return condition;
}


Container * XMLParser::parseContainer(TiXmlElement * element) {
    Container * container = new Container();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();
            
            if (name == "name")
                container->setName(value);
            else if (name == "description")
                container->setDescription(value);
            else if (name == "status")
                container->setStatus(value);
            else if (name == "accepts")
                container->addAccepts(value);
            else if (name == "trigger")
                container->addTrigger(parseTrigger(childElement));
            else if (name == "item")
            {
                Item* item = new Item();
                item->setName(value);
                container->addItem(item);
                std::cout << "\nItem in Container:" << std::endl;
                std::cout << item->getName() + ": " << static_cast<void*>(item) << std::endl;
                // item->printAttrs();
                // item->display();
                // container->addItem(parseItem(childElement));
            }
                
        }
    }
    container->display();
    bool inArray = 0;
    for (Container* c : containers) { if (c->getName() == container->getName()) inArray = 1; }
    if (!inArray)
        addContainer(container);
    return container;
}


Creature * XMLParser::parseCreature(TiXmlElement * element) 
{
    Creature * creature = new Creature();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "name")
                creature->setName(value);
            else if (name == "vulnerability")
                creature->addVulnerability(value);
            else if (name == "attack")
                creature->addAttack(parseAttack(childElement));
            else if (name == "trigger")
                creature->addTrigger(parseTrigger(childElement));
        }
    }
    // creature->display();
    bool inArray = 0;
    for (Creature* c : creatures) { if (c->getName() == creature->getName()) inArray = 1; }
    if (!inArray)
        addCreature(creature);
    return creature;
}


Item * XMLParser::parseItem(TiXmlElement * element) {
    Item * item = new Item();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "name")
                item->setName(value);
            else if (name == "writing")
                item->setWriting(value);
            else if (name == "status")
                item->setStatus(value);
            else if (name == "description")
                item->setDescription(value);
            else if (name == "turnon")
                item->setTurnon(parseTurnon(childElement));
            else if (name == "trigger")
                item->addTrigger(parseTrigger(childElement));
        }
    }
    item->printAttrs();
    // item->display();
    bool inArray = 0;
    for (Item* c : items) { if (c->getName() == item->getName()) inArray = 1; }
    if (!inArray)
        addItem(item);
    return item;
}


Room * XMLParser::parseRoom(TiXmlElement * element) 
{ 
    Room * room = new Room();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "name")
                room->setName(value);
            else if (name == "description")
                room->setDescription(value);
            else if (name == "status")
                room->setStatus(value);
            else if (name == "type")
                room->setType(value);
            else if (name == "border")
                room->addBorder(parseBorder(childElement));
            else if (name == "container") {
                // room->addContainer(parseContainer(childElement));
                Container* container = new Container();
                container->setName(value);
                room->addContainer(container);
                container->display();
                addContainer(container);
            }
            else if (name == "creature") {
                // room->addCreature(parseCreature(childElement));
                Creature* creature = new Creature();
                creature->setName(value);
                room->addCreature(creature);
                // creature->display();
                addCreature(creature);
            }
            else if (name == "item") {
                // room->addItem(parseItem(childElement));
                Item* item = new Item();
                item->setName(value);
                room->addItem(item);
                // item->printAttrs();
                // item->display();
                addItem(item);
            }
            else if (name == "trigger")
                room->addTrigger(parseTrigger(childElement));         
        }
    }
    // room->display();
    return room;
}


Trigger * XMLParser::parseTrigger(TiXmlElement * element) 
{
    Trigger * trigger = new Trigger();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "type")
                trigger->setType(value);
            else if (name == "command")
                trigger->setCommand(value);
            else if (name == "print")
                trigger->addPrints(value);
            else if (name == "action")
                trigger->addAction(value);
            else if (name == "condition")
                trigger->addCondition(parseCondition(element));
        }
    }
    // trigger->display();
    return trigger;
}


Turnon * XMLParser::parseTurnon(TiXmlElement * element)
{
    Turnon * turnon = new Turnon();
    for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        { 
            std::string name = childElement->ValueStr();
            std::string value = "";
            if (childElement->GetText() != NULL)
                value = childElement->GetText();

            if (name == "print")
                turnon->setPrint(value);
            else if (name == "action")
                turnon->addAction(value);
        }
    }
    // turnon->display();
    return turnon;
}


Map * XMLParser::parseMap(const char * filename) {
  TiXmlDocument doc(filename);
  doc.LoadFile();

  // fetch root elem
  TiXmlElement * rootElement = doc.RootElement();
  Map * map = new Map();
  if (rootElement != NULL && rootElement->ValueStr() == "map") 
  {
    for (TiXmlNode* node = rootElement->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        {
            std::string name = childElement->ValueStr();
            
            if (name == "room")
                map->addRoom(parseRoom(childElement));
            else if (name == "item")
            {
                Item * tempItem = parseItem(childElement);
                map->addItem(tempItem);
                for (Item* i : items)
                    if (i->getName() == tempItem->getName()) {
                        // std::cout << "\nItem Declaration: i" << std::endl;
                        // std::cout << i->getName() + ": " << static_cast<void*>(i) << std::endl;
                        // std::cout << "\nItem Declaration: temp" << std::endl;
                        // std::cout << tempItem->getName() + ": " << static_cast<void*>(tempItem) << std::endl;
                        *i = *tempItem;
                        // std::cout << "\nItem Declaration: i after" << std::endl;
                        // std::cout << i->getName() + ": " << static_cast<void*>(i) << std::endl;
                    }
            }
            else if (name == "creature")
            {
                Creature * tempCreature = parseCreature(childElement);
                map->addCreature(tempCreature);
                for (Creature* c : creatures)
                    if (c->getName() == tempCreature->getName())
                        *c = *tempCreature;
            }
            else if (name == "container")
            {
                Container * tempContainer = parseContainer(childElement);
                map->addContainer(tempContainer);
                for (Container* c : containers)
                    if (c->getName() == tempContainer->getName())
                        *c = *tempContainer;
            }
        }
    }
  }
  for (Container * c : map->getContainers()) {
      for (Item * cont_item : c->getItem()) {
          std::cout << "CONTAINER ITEM " + cont_item->getName() << std::endl;
          for(Item * map_item : map->getItems()) {
              std::cout << "MAP ITEM " + map_item->getName() << std::endl;
              if (cont_item->getName() == map_item->getName()) {
                  std::cout << "NAME MATCH " << std::endl;
                  *cont_item = *map_item;
                  std::cout << cont_item->getName() + ": " << static_cast<void*>(cont_item) << std::endl;
                  std::cout << map_item->getName() + ": " << static_cast<void*>(map_item) << std::endl;
              }
          }
      }
  }
    std::cout << std::endl; 
    // map->printEVERYTHING();
    return map;
}
