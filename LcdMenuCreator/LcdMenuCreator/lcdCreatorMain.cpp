#include "pugixml.hpp"
#include <iostream>
#include <vector>


#include "hw_Button.h"
#include "hw_Inputs.h"
#include "Line.h"
#include "ConfigManager.h"
#include "PageCreator.h"
#include "skeletonProcessor.h"

using namespace std;
using namespace pugi;

hw_Inputs *inputsPtr;

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("testFormat.xml",parse_ws_pcdata_single);
	
	std::cout << "Load result: " << result.description() << endl;

	hw_Inputs inputs( doc.child("Inputs") );
	inputsPtr=&inputs;
	//hw_Inputs inputs( doc.child("Inputs") );
	inputsPtr->display();

	ConfigManager config( doc.child("Config") );
	config.display();
	
	xml_node displayNode=doc.child("Display");

	skeletonProcessor sP;

	vector<PageCreator> p;

	for( xml_node::iterator it=displayNode.begin() ; it!=displayNode.end(); ++it)
	{
		p.push_back( PageCreator( *it ) );
	}
	//PageCreator p0( doc.child("Display").first_child() );
	//p0.display();

	//PageCreator p1( doc.child("Display").first_child().next_sibling() );
	//p1.display();
	
	int simply;
	cin>>simply;

}