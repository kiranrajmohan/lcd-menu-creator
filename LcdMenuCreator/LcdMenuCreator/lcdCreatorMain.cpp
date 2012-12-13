#include "pugixml.hpp"
#include <iostream>
#include <vector>
#include <fstream>

#include "hw_Button.h"
#include "hw_Inputs.h"
#include "Line.h"
#include "ConfigManager.h"
#include "PageCreator.h"
#include "skeletonProcessor.h"

using namespace std;
using namespace pugi;

hw_Inputs *inputsPtr;

int main()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("testFormat.xml",parse_ws_pcdata_single);
	
	std::cout << "Load result: " << result.description() << endl;

	hw_Inputs inputs( doc.child("Inputs") );
	inputsPtr=&inputs;
	//hw_Inputs inputs( doc.child("Inputs") );
	inputsPtr->display();

	ConfigManager config( doc.child("Config") );
	config.display();
	
	xml_node displayNode=doc.child("Display");

	skeletonProcessor sP;

	vector<PageCreator> p;

	string finalCode;


	int maxLines=0;
	for( xml_node::iterator it=displayNode.begin() ; it!=displayNode.end(); ++it)
	{
		p.push_back( PageCreator( *it ) );
		if(p.back().numLines>maxLines){
			maxLines=p.back().numLines;
		}
	}
	string maxL=to_string( long double( maxLines ) );
	finalCode.append("struct LineStatus{\n  \n\
		char showCursor,					\n\
		currentLine,						\n\
		currentPosIndex,					\n\
		numLines,							\n\
		lineCursorList[").append( maxL ).append("],\n")
		.append("lineIndicatorList[").append(maxL).append("],\n")
		.append("lineStart[").append(maxL).append("],\n")
		.append("navOn[2] \n};\n");

	
	finalCode+=sP.processed;

	finalCode+="\n//-----------------Page function------------------\n";
	for( vector<PageCreator>::iterator it=p.begin() ; it!=p.end(); ++it)
	{
		finalCode+="\n//----------------"+ it->name + "---------------------------\n";
		finalCode+=it->pageFunction;
	}
	finalCode+="\n//-----------------Page functions over------------------\n";

	ofstream of("createdCode.cpp");
	of<<finalCode;
	of.close();
	
	int simply;
	cin>>simply;

}