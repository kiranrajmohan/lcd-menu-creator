#include "hw_Inputs.h"
#include <iostream>

hw_Inputs::hw_Inputs(void)
{
}

hw_Inputs::hw_Inputs( xml_node inputs)
{
	for (xml_node_iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		hw_Button b( *it );
		inputButtons.insert( pair<string,hw_Button>( b.name(), b ) );
		if( b.action() == "up" ||
			b.action() == "down" || 
			b.action() == "right"  || 
			b.action() == "left" || 
			b.action() == "enter"  || 
			b.action() == "back"){
				actionButtons.insert( pair<string,hw_Button>( b.action(), b ) );
		}
	}
}

void hw_Inputs::display()
{
	int s=inputButtons.size();
	for(map<string,hw_Button>::iterator iter = inputButtons.begin(); iter != inputButtons.end(); iter++ ) {
        iter->second.display();
	}
	std::cout<< "actionButtons=> ";
	for(map<string,hw_Button>::iterator iter = actionButtons.begin(); iter != actionButtons.end(); iter++ ) {
		cout<<" "<< iter->first ;
	}
}

hw_Inputs::~hw_Inputs(void)
{
}
