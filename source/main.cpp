#include "../tinyxml/tinyxml.h"
#include "../header/XMLParser.h"
#include "../header/Player.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

std::vector<std::string> parse_put(std::vector<std::string> cmd_str);
template <typename T>
bool checkAllConditions(T * obj, Player * player, Map * map);
void notInInv(std::string item);

const unsigned int NUM_INDENTS_PER_SPACE=2;
const std::vector <std::string> VALID_CMDS = 
    {"n", "s", "e", "w",
    "north", "south", "east", "west",
    "i", "inventory",
    "take", "drop", "open", "read", "put", "turn", "attack",
    "current", "inventorystatus", "items", "containers"};

template <typename T>
T* contains(std::vector<T> vec, const T & elem){
    for (auto * a : vec) {
        if (a == elem)
            if (a->getDeleted() != true)
                return a;
    }
    return NULL;
}
template <typename T>
T contains(std::vector<T> vec, const std::string name) {
    for (auto * e : vec) {
        if (e->getName() == name)
            if (e->getDeleted() != true)
                return e;
    }
    return NULL;
}

std::string contains(std::vector<std::string> vec, const std::string name) {
    for (std::string e : vec) {
        std::cout << e << std::endl;
        if (e == name)
            return e;
    }
    return "";
}

const char * getIndent( unsigned int numIndents )
{
	static const char * pINDENT="                                      + ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

// same as getIndent but no "+" at the end
const char * getIndentAlt( unsigned int numIndents )
{
	static const char * pINDENT="                                        ";
	static const unsigned int LENGTH=strlen( pINDENT );
	unsigned int n=numIndents*NUM_INDENTS_PER_SPACE;
	if ( n > LENGTH ) n = LENGTH;

	return &pINDENT[ LENGTH-n ];
}

int dump_attribs_to_stdout(TiXmlElement* pElement, unsigned int indent)
{
	if ( !pElement ) return 0;

	TiXmlAttribute* pAttrib=pElement->FirstAttribute();
	int i=0;
	int ival;
	double dval;
	const char* pIndent=getIndent(indent);
	printf("\n");
	while (pAttrib)
	{
		printf( "%s%s: value=[%s]", pIndent, pAttrib->Name(), pAttrib->Value());

		if (pAttrib->QueryIntValue(&ival)==TIXML_SUCCESS)    printf( " int=%d", ival);
		if (pAttrib->QueryDoubleValue(&dval)==TIXML_SUCCESS) printf( " d=%1.1f", dval);
		printf( "\n" );
		i++;
		pAttrib=pAttrib->Next();
	}
	return i;	
}

void dump_to_stdout( TiXmlNode* pParent, unsigned int indent = 0 )
{
	if ( !pParent ) return;

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();
	printf( "%s", getIndent(indent));
	int num;

	switch ( t )
	{
	case TiXmlNode::TINYXML_DOCUMENT:
		printf( "Document" );
		break;

	case TiXmlNode::TINYXML_ELEMENT:
		printf( "Element [%s]", pParent->Value() );
		num=dump_attribs_to_stdout(pParent->ToElement(), indent+1);
		switch(num)
		{
			case 0:  printf( " (No attributes)"); break;
			case 1:  printf( "%s1 attribute", getIndentAlt(indent)); break;
			default: printf( "%s%d attributes", getIndentAlt(indent), num); break;
		}
		break;

	case TiXmlNode::TINYXML_COMMENT:
		printf( "Comment: [%s]", pParent->Value());
		break;

	case TiXmlNode::TINYXML_UNKNOWN:
		printf( "Unknown" );
		break;

	case TiXmlNode::TINYXML_TEXT:
		pText = pParent->ToText();
		printf( "Text: [%s]", pText->Value() );
		break;

	case TiXmlNode::TINYXML_DECLARATION:
		printf( "Declaration" );
		break;
	default:
		break;
	}
	printf( "\n" );
	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
	{
		dump_to_stdout( pChild, indent+1 );
	}
}

// load the named file and dump its structure to STDOUT
void dump_to_stdout(const char* pFilename)
{
	TiXmlDocument doc(pFilename);
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		printf("\n%s:\n", pFilename);
		dump_to_stdout( &doc ); // defined later in the tutorial
	}
	else
	{
		printf("Failed to load file \"%s\"\n", pFilename);
	}
}

std::string get_cmd_item(std::vector<std::string> cmd_str) {
    cmd_str.erase(cmd_str.begin());
    std::string item_name = "";
    for (auto s : cmd_str) {
        item_name += s + " ";
    }
    item_name.pop_back();
    return item_name;
}

void Add(std::string object, std::string destination, Map * map) {
    
    Room * destination_room = contains(map->getRooms(), destination);
    if (destination_room != NULL) {
        Item * item = contains(map->getItems(), object);
        if (item != NULL) {
            destination_room->addItem(item);
            item->setDeleted(false);
        }
        else {
            Container * container = contains(map->getContainers(), object);
            if (container != NULL) {
                destination_room->addContainer(container);
                container->setDeleted(false);
            }
            else {
                Creature * creature = contains(map->getCreatures(), object);
                if (creature != NULL) {
                    destination_room->addCreature(creature); 
                    creature->setDeleted(false);
                }
            }
        }
    }
    Container * destination_container = contains(map->getContainers(), destination);
    if (destination_container != NULL) {
        Item * item = contains(map->getItems(), object);
        if (item != NULL)
            destination_container->addItem(item);
    }    
}

void Delete(std::string object, Map * map) {
    Room * room = contains(map->getRooms(), object);
    Item * item = contains(map->getItems(), object);
    Container * container = contains(map->getContainers(), object);
    Creature * creature = contains(map->getCreatures(), object);

    if (room != NULL) { room->setDeleted(true); }
    if (item != NULL) { item->setDeleted(true); }
    if (container != NULL) { container->setDeleted(true); }
    if (creature != NULL) { creature->setDeleted(true); }
 }

void Update(std::string object, std::string status, Map * map){
    Room * room = contains(map->getRooms(), object);
    Item * item = contains(map->getItems(), object);
    Container * container = contains(map->getContainers(), object);
    Creature * creature = contains(map->getCreatures(), object);

    if (room != NULL) { room->setStatus(status); }
    if (item != NULL) { item->setStatus(status); }
    if (container != NULL) { container->setStatus(status); }
    if (creature != NULL) { creature->setStatus(status); }
}

void Drop(Player * player, std::string item) {
    Item * i = contains(player->getInventory(), item);
    if (i != NULL) player->drop(i);
    else notInInv(item);
}

void Take(Player * player, std::string item_name) {
    Item * i = contains(player->getCurrentRoom()->getItems(), item_name);
    Item * inv = contains(player->getInventory(), item_name);
    if (inv != NULL)
        std::cout << item_name + "already in inventory" << std::endl;
    else if (i != NULL)
        player->take(i);
    else {
        std::vector<Container*> cs = player->getCurrentRoom()->getContainers();
        for (auto c : cs) {
            i = contains(c->getItems(), item_name);
            if (i != NULL){
                if (c->isOpen()) {
                    if (i == NULL)
                        std::cout << "\tYou don't see a " + item_name + " to take..." << std::endl;
                    else 
                        player->take(i);
                } else {
                    std::cout << "\t" + c->getName() + " is not open." << std::endl;
                }
            }            
        }
    }
}

void Attack(Player * player, std::string creature_of_attack, std::string item, Map * map) {
    std::string item_of_attack = item; //  NEED: IMPLEMENT MULTI WORD HANDLING
    Creature * creature = contains(player->getCurrentRoom()->getCreatures(), creature_of_attack);
    if (creature == NULL)
        std::cout << "\tYou don't see a " + creature_of_attack + " in this room..." << std::endl;
    else if (contains(player->getInventory(), item_of_attack) == NULL)
        notInInv(item_of_attack);
    else {
        std::cout << "\tYou assault the " + creature_of_attack + " with the " + item_of_attack << std::endl;
        for (std::string v : creature->getVulnerabilities()) {
            if (v == item_of_attack) {
                checkAllConditions(creature->getAttack(), player, map);
            }
        }
    }
}

void Put(Player * player, std::vector<std::string> cmd_str) {
    std::vector<std::string> put_str = parse_put(cmd_str);
    if (!put_str.empty()) {
        Item * item = contains(player->getInventory(), put_str.at(0));
        if (item == NULL) 
            notInInv(put_str.at(0));
        else {
            Container * container = contains(player->getCurrentRoom()->getContainers(), put_str.at(1));
            if (container == NULL || container->getDeleted()) {
                std::cout << "\tYou cannot access that container!" << std::endl;
            } else if (!(container->getAccepts().empty())) {
                if (contains(container->getAccepts(), put_str.at(0)) != "") 
                    player->put(item, container);
            } else if (!container->isOpen()) {
                std::cout << "\tCannot put " + put_str.at(0) + " in closed " + put_str.at(1) + "." << std::endl;
            } else { 
                player->put(item, container);
            }
        }
    }
}

void Open(Player * player, std::string item_name, std::string full_cmd) {
    Container * c = contains(player->getCurrentRoom()->getContainers(), item_name);
    if (c != NULL) player->open(c);
    else if (full_cmd != "open exit") std::cout << "\tThere is no " + item_name + " to open..." << std::endl;
}

void Read(Player * player, std::string item_name) {
    Item * item = contains(player->getInventory(), item_name);
    if (item != NULL)
        player->read(item, item_name);
    else
        notInInv(item_name);
}

void Turn(Player * player, std::vector<std::string> cmd_str) {
    if (cmd_str.at(1) == "on") {
        cmd_str.erase(cmd_str.begin());
        std::string item_name = get_cmd_item(cmd_str);
        Item * item = contains(player->getInventory(), item_name);
        if (item == NULL)
            notInInv(item_name);
        else {
            item->turn_on();
            if (!(item->getTurnon()->getActions().empty())) {
                for (std::string a : item->getTurnon()->getActions()) {
                    std::vector<std::string> action_vec;
                    std::istringstream ss(a);
                    std::string word;
                    while (ss >> word) { action_vec.push_back(word); }

                    if (action_vec.front() == "drop")
                        Drop(player, action_vec.at(1));
                    action_vec.clear();
                }
            }
        }
    }
}

void GameOver(Map * map) {
    map->setGameOver(true);
}

void help() {
	// std::cout << "TODO: Implement help function." << std::endl;
    const char * help_text = "\n \
    Movement Commands: n, s, e, w\n \
    \t Type a movement command to move in the corresponding direction.\n\n \
    Inventory Commands: i\n \
    \t Press 'i' to view your inventory\n\n \
    Interaction Commands:\n \
    \t take <item>: takes the item and puts it in your inventory\n \
    \t drop <item>: drops the item and places it in the current room\n \
    \t read <item>: displays any writing on the item\n \
    \t turnon <item>: activates the item\n \
    \t open <container>: opens the container and displays the contents\n \
    \t put <item> in <container>: removes the item from your inventory and places it in the container\n \
    \t attack <creature> with <item>: attacks the creature with the item and displays the success or failure\n";
    std::cout << help_text << std::endl;
}

void notInInv(std::string item) {
    std::cout << "\t" + item + " is not in your inventory..." << std::endl;
}

bool valid_cmd(std::string cmd) {
    for (std::string c : VALID_CMDS) {
        if (cmd == c)
            return 1;
    }
    return 0;
}

std::vector<std::string> parse_put(std::vector<std::string> cmd_str) {
    std::vector<std::string> put_str;
    cmd_str.erase(cmd_str.begin());
    std::string item_name = "";
    while(cmd_str.front() != "in" && !cmd_str.empty()) {
        item_name += cmd_str.front() + " ";
        cmd_str.erase(cmd_str.begin());
    }
    if (cmd_str.empty())
        return put_str;

    item_name.pop_back();
    cmd_str.erase(cmd_str.begin());

    std::string cont_name = "";
    for (auto s : cmd_str) {
        cont_name += s + " ";
    }
    cont_name.pop_back();
    put_str = {item_name, cont_name};
    return put_str;
}

bool checkCondition(Condition* c, Player * player, Map * map){
    std::string type = c->getType();
    if(type == "owner") {
        // static_cast<OwnerCondition*>(c)->printAttrs();
        bool has = static_cast<OwnerCondition*>(c)->getHas();
        std::string object = static_cast<OwnerCondition*>(c)->getObject();
        std::string owner = static_cast<OwnerCondition*>(c)->getOwner();

        if (owner == "inventory") {
            if (has == (contains(player->getInventory(), object) != NULL))
                return true;
        }
        else if (player->getCurrentRoom()->getName() == owner) {
            if (has == (contains(player->getCurrentRoom()->getItems(), object) != NULL))
                return true;
        }
        else if (contains(player->getCurrentRoom()->getContainers(), owner) != NULL) {
            for (Container * container : player->getCurrentRoom()->getContainers()) {
                if (container->getName() == owner) {
                    if (has == (contains(container->getItems(), object) != NULL))
                        return true;
                }
            }
        }
    } 
    else if (type == "status") {
        // static_cast<StatusCondition*>(c)->printAttrs();
        std::string obj = static_cast<StatusCondition*>(c)->getObject();
        std::string status = static_cast<StatusCondition*>(c)->getStatus();
        for (Item * i : player->getInventory()) {
            if (i->getName() == obj) {
                if (i->getStatus() == status) {
                    return true;
                }
            }
        }
        for (Item * i : player->getCurrentRoom()->getItems()) {
            if ((i->getName() == obj) && (i->getStatus() == status))
                return true;
        }
        for (Container * container : player->getCurrentRoom()->getContainers()) {
            if ((container->getName() == obj) && (container->getStatus() == status))
                return true;
        }
    }
    return false;
}

template <typename T>
bool checkAllConditions(T * obj, Player * player, Map * map) {
    if (obj == NULL)
        return false;
    bool conditionsMet = true;
    for (Condition * c : obj->getConditions()) {
        conditionsMet &= checkCondition(c, player, map);
    }
    if (conditionsMet) {
        std::vector <std::string> action_vec;
        for(auto s : obj->getPrints())
            std::cout << "\t" + s << std::endl;
        for(auto a : obj->getActions()) {
            std::istringstream ss(a);
            std::string word;
            while (ss >> word) { action_vec.push_back(word); }

            std::string full_cmd;
            for (std::string s : action_vec) {
                full_cmd += s + " ";
            }
            full_cmd.pop_back();

            if (action_vec.front() == "Add")
                Add(action_vec.at(1), action_vec.at(3), map);
            else if (action_vec.front() == "Delete")
                Delete(action_vec.at(1), map);
            else if (action_vec.front() == "Update")
                Update(action_vec.at(1), action_vec.at(3), map);
            else if (action_vec.front() == "Game" && action_vec.at(1) == "Over")
                GameOver(map);
            else if (action_vec.front() == "drop")
                Drop(player, action_vec.at(1));
            else if (action_vec.front() == "attack")
                Attack(player, action_vec.at(1), action_vec.at(3), map);
            else if (action_vec.front() == "take")
                Take(player, action_vec.at(1));
            else if (action_vec.front() == "put")
                Put(player, action_vec);

            action_vec.clear();
        }
    }
    return conditionsMet;
}

bool checkCmdTriggers(std::vector<Trigger*> triggers, std::string cmd, Player * player, Map * map) {
    if (triggers.empty())
        return false;

    if (player->getCurrentRoom()->hasTrigger(cmd) == NULL)
        return false;

    bool condMet = true;
    for (Trigger * trigger : triggers) {
        if (trigger->getCommand() == cmd && trigger->getType() != "used") {
            condMet &= checkAllConditions(trigger, player, map);
        }
        if (condMet && trigger->getType() != "permanent") {
            trigger->setType("used");
        }
    }
    return condMet;
}

bool checkEffectTriggers(Player * player, Map * map) {
    bool condMet = false;
    bool return_val = false;
    for (Trigger * t : player->getCurrentRoom()->getTriggers()) {
        if (t->getCommand() == "" && t->getType() != "used") {
            return_val = checkAllConditions(t, player, map);
            condMet &= return_val;
        }
        if (return_val && t->getType() != "permanent") {
            t->setType("used");
        }
    }
    for (Container * c : player->getCurrentRoom()->getContainers()) {
        for (Trigger * t : c->getTriggers()) {
            if (t->getCommand() == "" && t->getType() != "used") {
                return_val = checkAllConditions(t, player, map);
                condMet &= return_val;
            }
            if (return_val && t->getType() != "permanent") {
                t->setType("used");
            }
        }
    }
    for (Creature * c : player->getCurrentRoom()->getCreatures()) {
        for (Trigger * t : c->getTriggers()) {
            if (t->getCommand() == "" && t->getType() != "used") {
                return_val = checkAllConditions(t, player, map);
                condMet &= return_val;
            }
            if (return_val && t->getType() != "permanent") {
                t->setType("used");
            }
        }
    }
    return condMet;
}


int main(int argc, char * argv[]) {
    XMLParser xml;
	if(argc != 2) {
		std::cout << "No XML file specified. Please specify an XML file as an argument to this program." << std::endl;
		return 0;
	}

    Map* map = xml.parseMap(argv[1]); 
	Player* player = new Player(map);
	std::string input = "";
	std::string command = "";
    std::vector <std::string> cmd_str;

	std::cout << "\n\n-------------Welcome to Zork!----------------" << std::endl;
	std::cout << "If you need help, type \"help\" or \"h\" at any point to get available commands.\n" << std::endl;
	help();
    std::cout << player->getCurrentRoom()->getDescription() << std::endl;
    

	do {
        cmd_str.clear();
		std::cout << "\nWhat would you like to do?" << std::endl;
		getline(std::cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        std::istringstream ss(input);
        std::string word;
        
        while (ss >> word) { cmd_str.push_back(word); }
        std::string full_cmd;
        for (std::string s : cmd_str) {
            full_cmd += s + " ";
        }
        full_cmd.pop_back();
        command = cmd_str.front();

        // Check if Command Overrides Trigger
        bool trig_override = false;
        trig_override |= checkCmdTriggers(player->getCurrentRoom()->getTriggers(), full_cmd, player, map);

        for (Item * i : player->getCurrentRoom()->getItems())
            trig_override |= checkCmdTriggers(i->getTriggers(), full_cmd, player, map);

        for (Item * i : player->getInventory())
            trig_override |= checkCmdTriggers(i->getTriggers(), full_cmd, player, map);    

        for (Container * c : player->getCurrentRoom()->getContainers())
            trig_override |= checkCmdTriggers(c->getTriggers(), full_cmd, player, map);  

        for (Creature * c : player->getCurrentRoom()->getCreatures())
            trig_override |= checkCmdTriggers(c->getTriggers(), full_cmd, player, map);  

        if (!valid_cmd(command)) {
            std::cout << "\n\tPlease type a valid command!\n\tPress 'h' to view them" << std::endl;
        } 
        else if (trig_override) {}
		else if(command == "n" || command == "s" || command == "e" || command == "w") {
            player->move(command, map);
		}
		else if(command == "north" || command == "south" || command == "east" || command == "west") {
			player->move(command, map);
		}
		else if(command == "i" || command == "inventory") {
			player->printInventory();
		}
        else if (command == "current") {
            player->getCurrentRoom()->printAttrs();
        }
        else if (command == "inventorystatus") {
            std::vector<Item *> items = player->getInventory();
            for (Item * i : items) {
                i->printAttrs();
            }
        }
        else if (command == "items"){
            std::cout << "Inventory Items: " << std::endl;
            for (Item * i : player->getInventory()) {
                std::cout << i->getName() + ": " << static_cast<void*>(i) << std::endl;
            }
            std::cout << "Room Items: " << std::endl;
            for (Item * i : player->getCurrentRoom()->getItems()) {
                std::cout << i->getName() + ": " << static_cast<void*>(i) << std::endl;
            }
            std::cout << "\nMap Items: " << std::endl;
            for (Item * i : map->getItems()) {
                std::cout << i->getName() + ": " << static_cast<void*>(i) << std::endl;

            }
            std::cout << "\nMap Item Descriptions: " << std::endl;
            map->printItems();
        }
        else if (command == "containers") {
            for(Container * c : player->getCurrentRoom()->getContainers()) {
                c->printAttrs();
            }
        }
        else if (cmd_str.size() == 1) {
            std::cout << "\n\t Please specify what item you would like to " + command + "!" << std::endl;
        }
		else if(command == "take") {
            std::string item_name = get_cmd_item(cmd_str);
            Take(player, item_name);
		}
		else if(command == "drop") {
            std::string item_name = get_cmd_item(cmd_str);
            Drop(player, item_name);
		}
        else if(command == "open") {
            std::string item_name = get_cmd_item(cmd_str);
            Open(player, item_name, full_cmd);
        }
        else if (command == "read") {
            std::string item_name = get_cmd_item(cmd_str);
            Read(player, item_name);
        }
        else if (command == "put") {
            Put(player, cmd_str);
        }
        else if (command == "turn") {
            Turn(player, cmd_str);
        }
        else if (command == "attack"){
            std::string creature_of_attack = cmd_str.at(1); // NEED: IMPLEMENT MULTI WORD HANDLING
            std::string item_of_attack = cmd_str.at(3); //  NEED: IMPLEMENT MULTI WORD HANDLING
            Attack(player, creature_of_attack, item_of_attack, map);
        }
		else if(command == "h" || command == "help") {
			help();
		}
        // bool check_trig = true;
        // while (check_trig) {
            checkEffectTriggers(player, map);
        // }
        
	} while(!(map->getGameOver()) && (input != "open exit" || !player->atExit()));

	std::cout << "\nVictory!" << std::endl;

    return 0;
}
