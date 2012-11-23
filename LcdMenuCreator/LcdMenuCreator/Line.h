#pragma once
#include "pugixml.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <bitset>

using namespace std;
using namespace pugi;


class Line
{
	enum commType{
		stringComm=0,
		fCallComm=1,
		condComm=2
	};

	struct commObj{
		int pos; //starting pos for strings
		string str,fCalls,cond;
		vector<commObj> commands; //nested commands for conditions

		commType type;
	};


	int num,length;
	vector<commObj> commands;
	
	static const map<string,int> componentStringMap;
	static const map<string,int> configStringMap;
	
	enum _configOptions
	{
		TakesCursor=0,
		LineIndicator
	};

	enum _componentStringIndex
	{
		String=0,
		Call,
		DisplayCall,
		UpdateIf,
		config,
		OnInput,
		Goto,
		CursorPos
	};

	void manageNode(xml_node n);
	void manageNode(xml_node n,vector<commObj> &commandVector);
	string generateString( xml_node n);
public:
	Line(void);
	Line( xml_node line ,int lineNo);
	
	bitset<2> configSelected;  //TakesCursor,LineIndicator
	vector<int> horizPos;


	void display();
	~Line(void);

	static map<string,int> createComponentStringMap();
	static map<string,int> createConfigStringMap();
};

