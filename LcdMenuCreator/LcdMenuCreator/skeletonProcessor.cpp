#include "skeletonProcessor.h"
#include <fstream>
#include <vector>
#include "ConfigManager.h"

void skeletonProcessor::loopOverLine(string &l,string templ, string actionString)
{
	int a=0;
	while( a!= string::npos ){
		a=l.find( templ,a );
		if( a!= string::npos ){
			l.replace( a, templ.length() , actionString );
			a+=actionString.length();
		}
	}

}

skeletonProcessor::skeletonProcessor(void)
{
	ifstream inf("LcdMenuCreator_codeSkeleton.cpp");

	if( !inf.good() ){
		return;
	}

	string l;
	vector<string> actions;
	actions.push_back("up");
	actions.push_back("down");
	actions.push_back("right");
	actions.push_back("left");

	while( getline(inf,l) ){

		for( vector<string>::iterator it=actions.begin(); it!=actions.end(); it++){
			if( inputsPtr->actionButtons.count( *it ) ){
				loopOverLine( l,"<"+*it + ">", inputsPtr->actionButtons[*it].isPressedChecker() );
			}
		}
		loopOverLine( l, "<LineIndicator>", "\""+ConfigManager::lineIndicator + "\"");
		loopOverLine( l, "<ActiveLineIndicator>", "\"" + ConfigManager::activeLineIndicator + "\"");
		loopOverLine( l, "<numLines>", "\"" + ConfigManager::activeLineIndicator + "\"");
		processed.append( l ).append("\n");
	}

	cout<<"\nprocessed =>\n"<<processed;
}




skeletonProcessor::~skeletonProcessor(void)
{
}
