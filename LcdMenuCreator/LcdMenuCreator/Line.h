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

	struct stringStruct{
		string s;
		int pos;
		stringStruct(){
			s=string("");
			pos=0;
		}
		stringStruct(string st,int p){
			s=st;
			pos=p;
		}
	};


	int num,
		length;
	vector<stringStruct> str;
	vector<string> fCalls;
	vector<string> conditions; //closing brackets are always inserted automatically
	
	bitset<2> configSelected;

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
		Goto
	};

	void manageNode(xml_node n);
	string generateString( xml_node n);
public:
	Line(void);
	Line( xml_node line ,int lineNo);

	void display();
	~Line(void);

	static map<string,int> createComponentStringMap();
	static map<string,int> createConfigStringMap();
};

