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
		int totalHorizPos, //total of all lines
			maxHorizPos,
			linesWithHorizPos; //highest of horizPos of all lines
		vector< vector<int> > horizPos;
	} horizPosStruct;

	string lineStatusGenerator();

public:
	PageCreator(void);
	PageCreator(xml_node n);

	void display();
	~PageCreator(void);
};

