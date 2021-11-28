#include "../tinyxml/tinyxml.h"
#include "../header/XMLParser.h"
#include "../header/Player.h"
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

const unsigned int NUM_INDENTS_PER_SPACE=2;
const std::vector <std::string> VALID_CMDS = 
    {"n", "s", "e", "w",
    "north", "south", "east", "west",
    "i", "inventory",
    "take", "drop", "open", "read", "put", "turn", "attack",
    "current", "inventorystatus", "items"};

template <typename T>
T* contains(std::vector<T> vec, const T & elem){
    for (auto * a : vec) {
        if (a == elem)
            return a;
    }
    return NULL;
}
template <typename T>
T contains(std::vector<T> vec, const std::string name) {
    for (auto * e : vec) {
        if (e->getName() == name)
            return e;
    }
    return NULL;
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

bool valid_cmd(std::string cmd) {
    for (std::string c : VALID_CMDS) {
        if (cmd == c)
            return 1;
    }
    return 0;
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
	std::cout << player->getCurrentRoom()->getDescription() << std::endl;
    help();

	do {
        cmd_str.clear();
		std::cout << "\nWhat would you like to do?" << std::endl;
		getline(std::cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        std::istringstream ss(input);
        std::string word;
        
        while (ss >> word) { cmd_str.push_back(word); }
        command = cmd_str.front();

        if (!valid_cmd(command)) {
            std::cout << "\n\tPlease type a valid command!\n\tPress 'h' to view them" << std::endl;
        }
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
            map->printItems();
        }
        else if (cmd_str.size() == 1) {
            std::cout << "\n\t Please specify what item you would like to " + command + "!" << std::endl;
        }
		else if(command == "take") {
            std::string item_name = get_cmd_item(cmd_str);
            Item * i = contains(player->getCurrentRoom()->getItem(), item_name);
            if (i == NULL) {
                std::vector<Container*> cs = player->getCurrentRoom()->getContainer();
                for (auto c : cs) {
                    if (c->isOpen())
                        i = contains(c->getItem(), item_name);
                }
            }
            if (i != NULL) player->take(i);
		}
		else if(command == "drop") {
            std::string item_name = get_cmd_item(cmd_str);
            Item * i = contains(player->getInventory(), item_name);
            if (i != NULL) player->drop(i);
		}
        else if(command == "open") {
            std::string item_name = get_cmd_item(cmd_str);
            Container * c = contains(player->getCurrentRoom()->getContainer(), item_name);
            if (c != NULL) player->open(c);
        }
        else if (command == "read") {
            std::string item_name = get_cmd_item(cmd_str);
            Item * item = contains(player->getInventory(), item_name);
            player->read(item, item_name);
        }
        else if (command == "put") {
            std::vector<std::string> put_str = parse_put(cmd_str);
            if (!put_str.empty()) {
                Item * item = contains(player->getInventory(), put_str.at(0));
                Container * container = contains(player->getCurrentRoom()->getContainer(), put_str.at(1));
                if (item == NULL) {
                    std::cout << "\t" + put_str.at(0) + " not in inventory" << std::endl;
                } else if (container == NULL) {
                    std::cout << "\tYou cannot access that container!" << std::endl;
                } else if (!container->isOpen()) {
                    std::cout << "\tCannot add " + put_str.at(0) + " to closed " + put_str.at(1) + "." << std::endl;
                } else { 
                    player->put(item, container);
                }
            }
        }
        else if (command == "turn") {
            if (cmd_str.at(1) == "on") {
                cmd_str.erase(cmd_str.begin());
                std::string item_name = get_cmd_item(cmd_str);
                Item * item = contains(player->getInventory(), item_name);
                if (item == NULL)
                    std::cout << "\t" + item_name + " not in inventory." << std::endl;
                else
                    item->turn_on();
            }
        }
        else if (command == "attack"){

        }
		else if(command == "h" || command == "help") {
			help();
		}
        
	} while(input != "open exit" || !player->atExit());

	std::cout << "\nVictory!" << std::endl;

    return 0;
}
