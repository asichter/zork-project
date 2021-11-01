#include "../tinyxml/tinyxml.h"
#include "../header/XMLParser.h"
#include "../header/Player.h"
#include <string>

const unsigned int NUM_INDENTS_PER_SPACE=2;

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
	std::cout << "TODO: Implement help function." << std::endl;
}

int main(int argc, char * argv[]) {
    XMLParser xml;
	if(argc != 2) {
		std::cout << "No XML file specified. Please specify an XML file as an argument to this program." << std::endl;
		return 0;
	}

    Map* map = xml.parseMap(argv[1]); 
	Player* player = new Player(map);
	std::string command = "";

	std::cout << "\n\n-------------Welcome to Zork!----------------" << std::endl;
	std::cout << "If you need help, type \"help\" or \"h\" at any point to get available commands.\n" << std::endl;
	std::cout << player->getCurrentRoom()->getDescription() << std::endl;

	do {
		std::cout << "\nWhat would you like to do?" << std::endl;
		getline(std::cin, command);

		if(command == "n" || command == "s" || command == "e" || command == "w") {
			player->move(command, map);
		}
		else if(command == "north" || command == "south" || command == "east" || command == "west") {
			player->move(command, map);
		}
		else if(command == "i" || command == "inventory") {
			player->printInventory();
		}
		else if(command.substr(0, 4) == "take") {
			std::vector<Item*> items = player->getCurrentRoom()->getItem();
			for(Item* i : items) {
				if(i->getName() == command.substr(5, command.size())) {
					player->take(i);
				}
			}

		}
		else if(command.substr(0, 4) == "drop") {
			std::vector<Item*> items = player->getInventory();
			for(Item* i : items) {
				if(i->getName() == command.substr(5, command.size())) {
					player->drop(i);
				}
			}
		}
		else if(command == "h" || command == "help") {
			help();
		}
	} while(command != "open exit" || !player->atExit());

	std::cout << "\nVictory!" << std::endl;

    return 0;
}
