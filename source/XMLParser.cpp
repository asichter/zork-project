#include "../tinyxml/tinyxml.h"
#include "../header/XMLParser.h"
#include <string>

void parseData() {
  char* filename = "./studentActivity.xml";
  TiXmlDocument doc(filename);
  doc.LoadFile();

  // fetch root elem
  TiXmlElement * rootElement = doc.RootElement();
  /*if (rootElement != NULL && rootElement->ValueStr() == "Students") {

  }*/
}