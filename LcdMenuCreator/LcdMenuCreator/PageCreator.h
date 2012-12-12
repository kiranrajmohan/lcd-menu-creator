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
	vector<Line> pageInputs;
	string name;
	int num;

	struct LineStatusStruct{
		int	showCursor,
				currentLine,
				currentPosIndex,
				numLines,
				navOn[2];
		vector<int>	lineCursorList,
						lineIndicatorList,
						lineStart;
	} lineStatus;

	struct HorizPosStruct{
		unsigned int totalHorizPos, //total of all lines
			maxHorizPos,
			linesWithHorizPos; //highest of horizPos of all lines
		vector< vector<int> > horizPos;
	} horizPosStruct;

	string lineStatusGenerator();
	string staticDisplayGenerator();
	string _updateLoopGenerator_conditions(vector<Line::commObj> &com);
	string _updateLoopGenerator_inputs(vector<Line::commObj> &com);
	string updateLoopGenerator();

public:
	PageCreator(void);
	PageCreator(xml_node n);

	string pageFunction;

	void display();
	~PageCreator(void);
	
};

