#include "pugixml.hpp"
#include <iostream>
#include <vector>


#include "hw_Button.h"
#include "hw_Inputs.h"
#include "Line.h"
#include "ConfigManager.h"
#include "PageCreator.h"

using namespace std;
using namespace pugi;

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("testFormat.xml",parse_ws_pcdata_single);
	
	std::cout << "Load result: " << result.description() << endl;
	
	//hw_Inputs inputs( doc.child("Inputs") );
	//inputs.display();

	ConfigManager config( doc.child("Config") );
	config.display();

	PageCreator p0( doc.child("Display").first_child() );
	p0.display();

	PageCreator p1( doc.child("Display").first_child().next_sibling() );
	p1.display();


	
	int simply;
	cin>>simply;

}