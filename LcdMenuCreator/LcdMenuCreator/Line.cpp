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
	m["CursorPos"]=CursorPos;
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
	length=0;
	num=lineNo;
	configSelected[0]=configSelected[1]=0;

	for( xml_node::iterator it=line.begin(); it!=line.end(); ++it)
	{
		manageNode( *it );
	}
}
void Line::manageNode(xml_node n)
{
	manageNode(n,commands); //add commands to the default command vector
}

void Line::manageNode(xml_node n,vector<commObj> &commandVector) //specify command vector for use with 
{
		string s=generateString( n );
		commObj c;
		//cout<<"\nmanageNode for"<<s<<endl;
		switch( componentStringMap.find( n.name())->second  )
		{
		case String:
			c.str=s;
			c.pos=length;
			c.type=stringComm;
			commandVector.push_back( c );
			length+=s.length();
			break;
		case Call:
			c.fCalls=s;
			c.type=fCallComm;
			commandVector.push_back( c );
			break;
		case DisplayCall:
			c.fCalls=s;
			c.type=fCallComm;
			commandVector.push_back( c );
			length+=atoi( n.attribute("maxLength").value() );
			break;
		case UpdateIf:
			c.cond=s;
			c.type=condComm;
			for( xml_node::iterator condChild=n.begin(); condChild!=n.end(); condChild++)
			{
				manageNode( *condChild, c.commands );
			}
			commandVector.push_back( c );
			break;
		case config:
			for( xml_node::iterator confChild=n.begin(); confChild!=n.end(); confChild++)
			{

				string str( confChild->name() );
				int num = configStringMap.find( str )->second;
				configSelected.flip( num ); //flip the corresponding bit of the bitset
			}
			break;
		
		case OnInput:
			c.cond=s;
			c.type=inputComm;
			for( xml_node::iterator condChild=n.begin(); condChild!=n.end(); condChild++)
			{
				manageNode( *condChild, c.commands );
			}
			commandVector.push_back( c );
			break;
		case Goto:
			c.type=fCallComm;
			c.fCalls=s;
			commandVector.push_back( c );
			break;
		case CursorPos:
			horizPos.push_back( length );
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

		case OnInput:
			s.append("if(isPressed(").append( string(n.attribute("input").value()) ).append(")){");
			break;

		case Goto:
			s.append("\tLoadMenu(").append( n.child_value() ).append(");\n\treturn;");
			break;

		case config:
			break;
		}

		return s;
}

void Line::display()
{
	struct Local
	{
		static void _disp( commObj c ){
			switch( c.type){
			case stringComm:
				//cout<<"string="<<c.str<<"@"<<c.pos<<endl;
				break;
			case  fCallComm:
				//cout<<"fCall="<<c.fCalls<<endl;
				break;
			case condComm:
				//cout<<"condition="<<c.cond<<endl;
				for(vector<commObj> ::iterator it=c.commands.begin(); it!=c.commands.end(); ++it){
					//cout<<"\t";
					Local::_disp(*it);
				}

			}
		}
	};



	//cout<<"\n------------------line "<<num<<"-------------------------"<< endl<<endl;

	for(vector<commObj> ::iterator it=commands.begin(); it!=commands.end(); ++it){
		Local::_disp(*it);
	}

	//cout<<"configSelected ==>" ;
	//cout<<configSelected.to_string();

	//cout<<"\nhorizPos=";
	for(vector<int> ::iterator it=horizPos.begin(); it!=horizPos.end(); ++it){
		//cout<<*it;
		//cout<<",";
	}
	
}


Line::~Line(void)
{
}
