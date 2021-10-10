#include "tinyxml/tinyxml.h"
#include "XMLParser.h"
#include <string>

void parseData() {
  std::string filename = "./studentActivity.xml";
  TiXmlDocument doc(filename);
  doc.LoadFile();

  // fetch root elem
  TiXmlElement * rootElement = doc.RootElement();
  if (rootElement != NULL && rootElement->ValueStr() == "Students") {

  }
}