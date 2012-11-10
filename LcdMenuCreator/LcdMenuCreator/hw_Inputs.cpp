#include "hw_Inputs.h"


hw_Inputs::hw_Inputs(void)
{
}

hw_Inputs::hw_Inputs( xml_node inputs)
{
	for (xml_node_iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		hw_Button b( *it );
		inputButtons.insert( pair<string,hw_Button>( b.name(), b ) );
	}
}

void hw_Inputs::display()
{
	int s=inputButtons.size();
	for(map<string,hw_Button>::iterator iter = inputButtons.begin(); iter != inputButtons.end(); iter++ ) {
        iter->second.display();
	}
}

hw_Inputs::~hw_Inputs(void)
{
}
