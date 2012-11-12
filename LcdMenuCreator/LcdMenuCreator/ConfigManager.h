#pragma once
#include <string>
#include "pugixml.hpp"
#include <iostream>

using namespace std;
using namespace pugi;

class ConfigManager
{
	
public:
	ConfigManager(void);
	ConfigManager( xml_node n);

	string activeLineIndicator,
		   lineIndicator;
	int maxLines,
		maxChar;

	void display();

	~ConfigManager(void);
};


