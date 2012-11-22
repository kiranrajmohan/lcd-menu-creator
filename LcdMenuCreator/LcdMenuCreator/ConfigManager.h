#pragma once
#include <string>
#include "pugixml.hpp"
#include <iostream>

using namespace std;
using namespace pugi;

class ConfigManager
{
	
public:
	ConfigManager( void );
	ConfigManager( xml_node n );

	static string activeLineIndicator,
		   lineIndicator;

	static int maxLines,
			maxChar,
			maxLineIndicatorLength;

	void display();

	~ConfigManager(void);

};


