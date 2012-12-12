#pragma once
#include <map>

#include "pugixml.hpp"
#include "hw_Button.h"

using namespace std;

class hw_Inputs
{

public:
	map<string,hw_Button> inputButtons;
	map<string,hw_Button> actionButtons;

	hw_Inputs(void);
	hw_Inputs( xml_node );

	void display();

	~hw_Inputs(void);
};

