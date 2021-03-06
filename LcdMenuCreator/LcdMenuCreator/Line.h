#pragma once
#include "pugixml.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <bitset>

#include "hw_Inputs.h"

using namespace std;
using namespace pugi;

extern hw_Inputs *inputsPtr;

class Line
{
public:
	enum commType{
		stringComm=0,
		fCallComm=1,
		condComm=2,
		inputComm=3,
	};

	struct commObj{
		int pos; //starting pos for strings
		string str,fCalls,cond;
		vector<commObj> commands; //nested commands for conditions

		commType type;
	};
	vector<commObj> commands;
	int num,length;

private:
	
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

	friend class PageCreator;
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

