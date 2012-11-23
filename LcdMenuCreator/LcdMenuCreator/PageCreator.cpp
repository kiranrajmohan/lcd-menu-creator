#include "PageCreator.h"
#include "ConfigManager.h"
#include <algorithm>
#include <sstream>

PageCreator::PageCreator(void)
{
}

PageCreator::PageCreator(xml_node n)
{
	name=string( n.attribute("name").as_string() );
	num=0;
	lineStatus.navOn[0]=lineStatus.navOn[1]=0;
	horizPosStruct.totalHorizPos=0;
	horizPosStruct.maxHorizPos=0;
	horizPosStruct.linesWithHorizPos=0;
	for( xml_node::iterator it=n.begin(); it!=n.end(); ++it)
	{
		if( string(it->name())==string("Line") ){
			Line l=Line( *it, num);
			lineStatus.lineCursorList.push_back( l.configSelected[0] ); //use TakesCursor
			lineStatus.lineIndicatorList.push_back( l.configSelected[1] ); //use LineIndicator
			lineStatus.lineStart.push_back( l.configSelected[1] *  ConfigManager::maxLineIndicatorLength ); //will be zero if lineIndicator is not set for the line ( l.configSelected[1] )

			if( l.horizPos.size()==0 ){
				vector<int> emptyHorizPos;
				emptyHorizPos.push_back(-1);
				horizPosStruct.horizPos.push_back( emptyHorizPos );
			}else{
				horizPosStruct.totalHorizPos+=l.horizPos.size(); //total of all lines
				if( l.horizPos.size() > horizPosStruct.maxHorizPos ){
					horizPosStruct.maxHorizPos=l.horizPos.size() ;
				}
				horizPosStruct.horizPos.push_back( l.horizPos );
				lineStatus.lineStart[num]=l.horizPos[0]; //if there are CursorPos, ignore default one and take the 1st explicit one
				horizPosStruct.linesWithHorizPos++;
			}
			lines.push_back( l );

		}else if( string(it->name())==string("OnInput") ){
			//TODO: complete
		}
	}
	lineStatusGenerator();
}

string PageCreator::lineStatusGenerator(){
	string s("LineStatus i={");

	s.append("0,");

	vector<int>::iterator it	= find( lineStatus.lineCursorList.begin(), lineStatus.lineCursorList.end(), 1); //first line that takes a cursor
	lineStatus.currentLine		= it - lineStatus.lineCursorList.begin(); //subtract pointers to find index
	lineStatus.currentPosIndex	= lineStatus.lineStart[ lineStatus.currentLine ]; //first pos of the currentLien

	s.append( to_string( long double(lineStatus.currentLine)) ).append(","); //convert to string and append
	s.append( to_string( long double(lineStatus.currentPosIndex)) ).append(","); //convert to string and append
	s.append( to_string( long double( lineStatus.lineCursorList.size() ) )).append(",{"); //convert to string and append


	std::stringstream ss;
	for(size_t i = 0; i < lineStatus.lineCursorList.size(); ++i)
	{
	  if(i != 0) ss << ",";
	  ss << lineStatus.lineCursorList[i];
	  if( lineStatus.lineCursorList[i] == 1 ){ lineStatus.navOn[1]++;  }
	}

	if( lineStatus.navOn[1] > 1 || horizPosStruct.linesWithHorizPos>1){ 
		lineStatus.navOn[1]=1; 
	}else{
		lineStatus.navOn[1]=0;
	}

	if( horizPosStruct.maxHorizPos > 1 ){
		lineStatus.navOn[0]=1;
	}

	s.append( ss.str() ).append("},{");
	ss.str(""); //clear the stream
	for(size_t i = 0; i < lineStatus.lineCursorList.size(); ++i)
	{
	  if(i != 0) ss << ",";
	  ss << lineStatus.lineIndicatorList[i];
	}
	s.append( ss.str() ).append("},{");
	ss.str(""); //clear the stream
	for(size_t i = 0; i < lineStatus.lineCursorList.size(); ++i)
	{
	  if(i != 0) ss << ",";
	  ss << lineStatus.lineStart[i];
	}
	s.append( ss.str() ).append("},{");
	s.append( to_string( long double( lineStatus.navOn[0] ) )).append(","); //convert to string and append
	s.append( to_string( long double( lineStatus.navOn[1] ) )).append("}};"); //convert to string and append

	cout<<endl<<s;

	return s;
}

void PageCreator::display()
{
	cout<<" Number of lines ="<<num;
	for( vector<Line>::iterator it=lines.begin() ; it!=lines.end(); ++it)
	{
		it->display();
		cout<<endl<<"--------------------------------------------------"<<endl;
	}


}


PageCreator::~PageCreator(void)
{
}
