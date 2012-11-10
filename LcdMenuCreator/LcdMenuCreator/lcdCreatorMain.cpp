#include "pugixml.hpp"
#include <iostream>
#include <vector>


#include "hw_Button.h"
#include "hw_Inputs.h"

using namespace std;
using namespace pugi;

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("testFormat.xml");
	
	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("Inputs").child("Button").attribute("name").value() << std::endl;
	std::cout << "Load result: " << result.description() << ", node name: " << doc.name() << std::endl;
	std::cout << "Load result: " << result.description() << ", node name: " << doc.first_child().name() << std::endl;
	
	
	//xml_node Inputs = doc.child("Inputs");
	hw_Inputs inputs( doc.child("Inputs") );
	inputs.display();
	//hw_Button b_up( Inputs.first_child() );
	//b_up.display();

	

	int simply;
	cin>>simply;
}