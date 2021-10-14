#include "../header/XMLParser.h"
#include <string>
#include <iostream>

Attack * parseAttack(TiXmlElement * element) 
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
    attack->display();
    return attack;
}

Border * parseBorder(TiXmlElement * element) 
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
    border->display();
    return border;   
}

Condition * parseCondition(TiXmlElement * element) 
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

    condition->display();
    return condition;
}

Container * parseContainer(TiXmlElement * element) {
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
                container->addTrigger(parseTrigger(element));
            else if (name == "item")
                container->addItem(parseItem(element));
        }
    }
    container->display();
    return container;
}

Creature * parseCreature(TiXmlElement * element) 
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
    creature->display();
    return creature;
}

Item * parseItem(TiXmlElement * element) {
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
    item->display();
    return item;
}

Room * parseRoom(TiXmlElement * element) 
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
            else if (name == "container")
                room->addContainer(parseContainer(childElement));
            else if (name == "creature")
                room->addCreature(parseCreature(childElement));
            else if (name == "item")
                room->addItem(parseItem(childElement));
            else if (name == "trigger")
                room->addTrigger(parseTrigger(childElement));         
        }
    }
    room->display();
    return room;
}

Trigger * parseTrigger(TiXmlElement * element) 
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
    trigger->display();
    return trigger;
}

Turnon * parseTurnon(TiXmlElement * element)
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
    turnon-display();
    return turnon;
}

    //  *  = new ();
    // for (TiXmlNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) 
    // {
    //     TiXmlElement * childElement = node->ToElement();
    //     if (childElement != NULL)
    //     { 
    //         std::string name = childElement->ValueStr();
    //         std::string value = "";
    //         if (childElement->GetText() != NULL)
    //             value = childElement->GetText();
    //     }
    // }
    // return ;

void parseMap(const char * filename) {
  TiXmlDocument doc(filename);
  doc.LoadFile();

  // fetch root elem
  TiXmlElement * rootElement = doc.RootElement();
  if (rootElement != NULL && rootElement->ValueStr() == "map") 
  {
    
    Map * map = new Map();
    for (TiXmlNode* node = rootElement->FirstChild(); node != NULL; node = node->NextSibling()) 
    {
        
        TiXmlElement * childElement = node->ToElement();
        if (childElement != NULL)
        {
            std::string name = childElement->ValueStr();
            
            if (name == "room")
                map->addRoom(parseRoom(childElement));
            else if (name == "item")
              map->addItem(parseItem(childElement));
            else if (name == "creature")
                map->addCreature(parseCreature(childElement));
                else if (name == "container")
                  map->addContainer(parseContainer(childElement));
        }
    }
    
  }
  map->display();
}
