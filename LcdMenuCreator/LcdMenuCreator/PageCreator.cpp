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
			num++;
		}else if( string(it->name())==string("OnInput") ){
			Line l;
			l.manageNode( *it); //update with only the OnInput Node
			pageInputs.push_back( l );
		}
	}
	pageFunction.append( "void generatedMenu_").append( name ).append("(){\n");
	pageFunction+=lineStatusGenerator()+"\n";
	pageFunction+=staticDisplayGenerator()+"\n";
	pageFunction+=updateLoopGenerator()+"\n";
	pageFunction+="\n}\n";
	cout<<"\n\npageFunction-------------------\n\n"<<pageFunction<<"\n-------------------------------\n";
}

string PageCreator::lineStatusGenerator(){
	string s("LineStatus i={");

	s.append("0,");

	vector<int>::iterator it	= find( lineStatus.lineCursorList.begin(), lineStatus.lineCursorList.end(), 1); //first line that takes a cursor
	lineStatus.currentLine		= it - lineStatus.lineCursorList.begin(); //subtract pointers to find index
	if( lineStatus.currentLine > lineStatus.lineStart.size()-1 ){ //no line takes cursor
		lineStatus.currentLine=0; //keep the first line to take cursor
	}
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

	//cout<<endl<<s;

	return s;
}

string PageCreator::staticDisplayGenerator(){
	
	string s("");
	for( vector<Line>::iterator lineIt=lines.begin() ; lineIt!=lines.end(); ++lineIt)
	{
		for( vector<Line::commObj>::iterator commIt=lineIt->commands.begin() ; commIt!=lineIt->commands.end(); ++commIt)
		{
			if( commIt->type == Line::commType::stringComm ){
				s.append("\nlcd_gotoxy(");
				s.append( to_string( long double( commIt->pos + lineStatus.lineStart[lineIt->num] ) )).append(",");
				s.append( to_string( long double( lineIt->num  ) )).append(");");
				s.append("\nlcd_puts_P(\"").append( commIt->str ).append("\");");
			}
		}
	}
//	cout<<"staticDisplayGenerator"<<endl<<s;
	return s;
}

string PageCreator::_updateLoopGenerator_conditions(vector<Line::commObj> &com)
{
	string s;
	for( vector<Line::commObj>::iterator commIt=com.begin() ; commIt!=com.end(); ++commIt)
	{
		if( commIt->type == Line::commType::fCallComm ){
			s.append("\n").append( commIt->fCalls );
		}else if( commIt->type == Line::commType::condComm ){
			s.append("\n").append( commIt->cond );
			s.append( _updateLoopGenerator_conditions( commIt->commands ) ).append("\n}");
		}
	}
	return s;
}

string PageCreator::_updateLoopGenerator_inputs(vector<Line::commObj> &com)
{
	string s;
	for( vector<Line::commObj>::iterator commIt=com.begin() ; commIt!=com.end(); ++commIt)
	{
		if( commIt->type == Line::commType::fCallComm ){
			s.append("\n\t").append( commIt->fCalls );
		}else if( commIt->type == Line::commType::condComm ||
					commIt->type == Line::commType::inputComm ){
			s.append("\n\t").append( commIt->cond );
			s.append( _updateLoopGenerator_conditions( commIt->commands ) ).append("\n}");
		}
	}
	return s;
}

string PageCreator::updateLoopGenerator(){
	string s("\nwhile(1){\n");
	for( vector<Line>::iterator lineIt=lines.begin() ; lineIt!=lines.end(); ++lineIt)
	{
		s.append( _updateLoopGenerator_conditions(lineIt->commands) );
	}

	s.append("\n navManager(i);\n if( display.toUpdate){\n \tprintLineIndicator(i); \n }");
	
	for( vector<Line>::iterator lineIt=pageInputs.begin() ; lineIt!=pageInputs.end(); ++lineIt)
	{
		for( vector<Line::commObj>::iterator commIt=lineIt->commands.begin() ; commIt!=lineIt->commands.end(); ++commIt)
		{
			if( commIt->type == Line::commType::inputComm ){
				s.append("\n\t").append( commIt->cond );
				s.append( _updateLoopGenerator_inputs( commIt->commands ) ).append("\n\t}\n");
			}
		}
	}

	for( vector<Line>::iterator lineIt=lines.begin() ; lineIt!=lines.end(); ++lineIt)
	{
		string inputLineCond;
		inputLineCond.append("\n if( i.currentLine==").append( to_string( long double( lineIt->num ) ) ).append("){");

		string temp;
		for( vector<Line::commObj>::iterator commIt=lineIt->commands.begin() ; commIt!=lineIt->commands.end(); ++commIt)
		{
			if( commIt->type == Line::commType::inputComm ){
				temp.append("\n\t").append( commIt->cond );
				temp.append( _updateLoopGenerator_inputs( commIt->commands ) ).append("\n\t}\n");
			}
		}
		if( temp.length() >0 ){
			s.append( inputLineCond ).append( temp ).append("\n}\n");
		}
	}

	

	s.append("\n}\n");

	//cout<<endl<<" loop generated\n"<<s;

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
