#pragma once
#include <iostream>
#include "pugixml.hpp"
#include "Line.h"
#include <string>

using namespace std;
using namespace pugi;

class PageCreator
{
	vector<Line> lines;
	string name;
	int num;
public:
	PageCreator(void);
	PageCreator(xml_node n);

	void display();
	~PageCreator(void);
};

