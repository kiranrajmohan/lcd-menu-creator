#pragma once
#include "pugixml.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace pugi;

class Line
{
	int num,
		length;
	vector<string> str;
	vector<string> fCalls;
	static const map<string,int> componentStringMap;
	
	enum _componentStringIndex
	{
		String=0,
		Call,
		DisplayCall,
		UpdateIf,
		config,
		OnInput
	} componentStringIndex;
public:
	Line(void);
	Line( xml_node line ,int lineNo);

	void display();
	~Line(void);

	static map<string,int> createStringMap();
};

