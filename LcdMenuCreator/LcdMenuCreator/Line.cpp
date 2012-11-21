#include "Line.h"

map<string,int> Line::createComponentStringMap()
{
	map<string,int> m;
	m["String"]=String;
	m["Call"]=Call;
	m["DisplayCall"]=DisplayCall;
	m["UpdateIf"]=UpdateIf;
	m["config"]=config;
	m["OnInput"]=OnInput;
	m["Goto"]=Goto;
	return m;
}

map<string,int> Line::createConfigStringMap()
{
	map<string,int> m;
	m["TakesCursor"]=TakesCursor;
	m["LineIndicator"]=LineIndicator;

	return m;
}

const map<string,int> Line::componentStringMap= Line::createComponentStringMap();
const map<string,int> Line::configStringMap= Line::createConfigStringMap();

Line::Line(void)
{
}

Line::Line(xml_node line,int lineNo)
{
	str.push_back( stringStruct() );
	length=0;
	num=lineNo;

	for( xml_node::iterator it=line.begin(); it!=line.end(); ++it)
	{
		manageNode( *it );
	}
}

void Line::manageNode(xml_node n)
{
		string s=generateString( n );
		switch( componentStringMap.find( n.name())->second  )
		{
		case String:
			str.back().s.append( s );
			str.back().pos=length;
			length+=s.length();
			break;
		case Call:
			fCalls.push_back(s);
			str.push_back( stringStruct()  ); //start a new string block
			conditions.push_back( string("") );
			break;
		case DisplayCall:
			fCalls.push_back(s);
			str.push_back( stringStruct()  ); //start a new string block
			conditions.push_back( string("") );
			length+=atoi( n.attribute("maxLength").value() );
			break;
		case UpdateIf:
			conditions.push_back( s );
			str.push_back( stringStruct()  ); 
			fCalls.push_back(string(""));
			for( xml_node::iterator condChild=n.begin(); condChild!=n.end(); condChild++)
			{
				manageNode( *condChild );
			}
			break;
		case config:
			for( xml_node::iterator confChild=n.begin(); confChild!=n.end(); confChild++)
			{

				string str( confChild->name() );
				int num = configStringMap.find( str )->second;
				configSelected.flip( num ); //flip the corresponding bit of the bitset
			}
			break;
		}
}

string Line::generateString( xml_node n)
{
	/*
			make the longest string (including spaces that is possible without breaks
			eg: "abcde  ",fCall,fCall,"  ghijk  ",
		*/
	string s("");
		switch( componentStringMap.find( n.name())->second  )
		{
		case String:
			s.append(n.child_value());
			break;

		case Call:
		case DisplayCall:
			for( xml_node::iterator callChildren=n.begin(); callChildren!=n.end(); ++callChildren)
			{
				if( callChildren->name() == string("Pos")){
					s+=std::to_string( static_cast<long long>(length) );
				}else if( callChildren->name() == string("Line" )){
					s+=std::to_string( static_cast<long long>(num) );
				}else if( callChildren->type() == node_pcdata ){
					s+=callChildren->value();
				}
			}
			s+=";";
			break;

		case UpdateIf:
			s+=string("if(") + n.attribute("cond").as_string() +string(")\n{");
			break;


			//TODO: complete
		case config:
			break;
		}

		return s;
}

void Line::display()
{
	cout<<"\n------------------line "<<num<<"-------------------------"<< endl<<endl;
	cout<<"**********str ************"<<str.size()<<endl ;
	for(vector<stringStruct>::iterator it=str.begin(); it!=str.end(); ++it){
		cout<<it->s<<"@"<<it->pos<<endl;
	}
	cout<<"**********fCalls ************"<<fCalls.size()<<endl ;
	for(vector<string>::iterator it=fCalls.begin(); it!=fCalls.end(); ++it){
		cout<<*it<<endl;
	}
	cout<<"**********conditions *************"<<conditions.size()<<endl ;
	for(vector<string>::iterator it=conditions.begin(); it!=conditions.end(); ++it){
		cout<<*it<<endl;
	}
	cout<<"configSelected ==>" ;
	cout<<configSelected.to_string();
}


Line::~Line(void)
{
}
