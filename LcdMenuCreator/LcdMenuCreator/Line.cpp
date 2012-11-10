#include "Line.h"

map<string,int> Line::createStringMap()
{
	map<string,int> m;
	m["String"]=String;
	m["Call"]=Call;
	m["DisplayCall"]=DisplayCall;
	m["UpdateIf"]=UpdateIf;
	m["config"]=config;
	m["OnInput"]=OnInput;
	return m;
}

const map<string,int> Line::componentStringMap= Line::createStringMap() ;

Line::Line(void)
{
}

Line::Line(xml_node line,int lineNo)
{
	str.push_back( string("") );
	length=0;
	num=lineNo;

	for( xml_node::iterator it=line.begin(); it!=line.end(); ++it)
	{
		/*
			make the longest string (including spaces that is possible without breaks
			eg: "abcde  ",fCall,fCall,"  ghijk  ",
		*/
		switch( componentStringMap.find( it->name())->second  )
		{
		case String:
			str.back().append(it->child_value());
			length+=string( it->text().as_string() ).length();
			cout<<"string==>"<<length<<"==>"<<str.back()<<endl;
			break;
		case DisplayCall:
			string call;
			cout<<"DisplayCall==>"<<length<<endl;
			for( xml_node::iterator callChildren=it->begin(); callChildren!=it->end(); ++callChildren)
			{
				if( callChildren->name() == string("Pos")){
					cout<<"Pos==>"<<std::to_string( static_cast<long long>(length)) <<endl;
					call+=std::to_string( static_cast<long long>(length) );
				}else if( callChildren->name() == string("Line" )){
					cout<<"Line==>"<<std::to_string( static_cast<long long>(num)) <<endl;
					call+=std::to_string( static_cast<long long>(num) );
				}else if( callChildren->type() == node_pcdata ){
					call+=callChildren->value();
				}
			}
			call+=";";
			length+=atoi( it->attribute("maxLength").value() );
			fCalls.push_back( call );
			str.push_back( string("") ); //start a new string block
			break;

			//TODO: complete.
		}
	}
}

void Line::display()
{
	for(vector<string>::iterator it=str.begin(); it!=str.end(); ++it){
		cout<<*it<<endl;
	}
	for(vector<string>::iterator it=fCalls.begin(); it!=fCalls.end(); ++it){
		cout<<*it<<endl;
	}
}


Line::~Line(void)
{
}
