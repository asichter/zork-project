#include "../header/XMLParser.h"
#include <string>
#include <iostream>
#include <vector>

void XMLParser::addItem(Item* item) { items.push_back(item); }
void XMLParser::addCreature(Creature * creature) { creatures.push_back(creature); }
void XMLParser::addContainer(Container * container) { containers.push_back(container); }
void XMLParser::addTrigger(Trigger * trigger) { triggers.push_back(trigger); }

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
                attack->addPrint(value); 
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
        condition = new OwnerCondition((has == "yes"), object, owner);
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
            else if (name == "accept")
                container->addAccepts(value);
            else if (name == "trigger")
                container->addTrigger(parseTrigger(childElement));
            else if (name == "item")
            {
                Item* item = new Item();
                item->setName(value);
                container->addItem(item);
                // container->addItem(parseItem(childElement));
            }
                
        }
    }
    //container->display();
    // container->printAttrs();
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
    // item->printAttrs();
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
                Container* container = new Container();
                container->setName(value);
                room->addContainer(container);
                // container->display();
                addContainer(container);
            }
            else if (name == "creature") {
                Creature* creature = new Creature();
                creature->setName(value);
                room->addCreature(creature);
                // creature->display();
                addCreature(creature);
            }
            else if (name == "item") {
                Item* item = new Item();
                item->setName(value);
                room->addItem(item);
                // item->printAttrs();
                // item->display();
                addItem(item);
            }
            else if (name == "trigger") {
                Trigger * trigger = new Trigger();
                room->addTrigger(parseTrigger(childElement));         
                addTrigger(trigger);
            }
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
            else if (name == "condition") {
                trigger->addCondition(parseCondition(childElement));
            }
                
        }
    }
    // trigger->printAttrs();
    // std::cout << std::endl;
    addTrigger(trigger);
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
                // map->addItem(tempItem);
                for (Item* i : items)
                    if (i->getName() == tempItem->getName()) {
                        *i = *tempItem;
                    }
            }
            else if (name == "creature")
            {
                Creature * tempCreature = parseCreature(childElement);
                // map->addCreature(tempCreature);
                for (Creature* c : creatures)
                    if (c->getName() == tempCreature->getName())
                        *c = *tempCreature;
            }
            else if (name == "container")
            {
                Container * tempContainer = parseContainer(childElement);
                // map->addContainer(tempContainer);
                for (Container* c : containers)
                    if (c->getName() == tempContainer->getName())
                        *c = *tempContainer;
            }
        }
    }
  }
    for (Container * c : containers) {
        for (Item * cont_item : c->getItems()) {
            for(Item * map_item : items) {
                if (cont_item->getName() == map_item->getName()) {
                    *cont_item = *map_item;
                    map->addItem(cont_item);
                }
            }
        }
    }
    
    for (Item * parser_item : items) {
        bool inArray = 0;
        for (Item * map_item : map->getItems()){
            if (parser_item->getName() == map_item->getName()) inArray = 1; 
        }
        if (!inArray)
            map->addItem(parser_item);
    }
    for (Creature * c : creatures)
        map->addCreature(c);
    for (Container * c : containers)
        map->addContainer(c);
    for (Trigger * t : triggers)
        map->addTrigger(t);
    // map->printEVERYTHING();
    return map;
}
