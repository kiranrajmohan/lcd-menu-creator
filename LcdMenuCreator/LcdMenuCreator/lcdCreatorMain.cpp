#include "pugixml.hpp"
#include <iostream>
#include <vector>


#include "hw_Button.h"
#include "hw_Inputs.h"
#include "Line.h"

using namespace std;
using namespace pugi;

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("testFormat.xml",parse_ws_pcdata_single);
	
	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("Inputs").child("Button").child("P").first_child().type() << std::endl;
	std::cout << "Load result: " << result.description() << ", node name: " << doc.name() << std::endl;
	std::cout << "Load result: " << result.description() << ", node name: " << doc.first_child().name() << std::endl;
	
	//hw_Inputs inputs( doc.child("Inputs") );
	//inputs.display();

	Line l( doc.child("Display").first_child().first_child(), 0);
	l.display();


	
	int simply;
	cin>>simply;

}