
#include "../BioWar_v0.01/tinyxml2.h"
#include <iostream>

int main()
{
   tinyxml2::XMLDocument doc;
   doc.Parse( "enemies.xml" );

   tinyxml2::XMLElement * element =  doc.FirstChildElement( "document" );;//->FirstChildElement( "data" )->FirstChild()->ToText();
   //tinyxml2::XMLText * text = doc.FirstChildElement( "document" );;//->FirstChildElement( "data" )->FirstChild()->ToText();
  
   //std::cout << text->Value() << std::endl;
}
