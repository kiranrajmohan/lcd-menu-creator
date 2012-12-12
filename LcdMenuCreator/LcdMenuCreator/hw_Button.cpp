#include "hw_Button.h"
#include <iostream>
using namespace std;

hw_Button::hw_Button(void)
{
}

hw_Button::hw_Button( string _name, string p, string ddr, string pin, string port, int _active, string _action)
{
	assign( _name, p,ddr,pin,port,active,_action);
}

hw_Button::hw_Button( xml_node button )
{
	bname=button.attribute("name").value();
	baction=button.attribute("action").value();
	P=button.child_value("P");
	DDR=button.child_value("DDR");
	PIN=button.child_value("PIN");
	PORT=button.child_value("PORT");
	if( button.child_value("Active")=="high" )
		active=high;
	else
		active=low;
}

void hw_Button::assign(string _name, string p, string ddr, string pin, string port, int _active, string _action )
{
	bname=_name;
	P=p;
	DDR=ddr;
	PIN=pin;
	PORT=port;
	baction=_action;
	if( _active = 1)
		active=high;
	else
		active=low;
}

string hw_Button::name()
{
	return bname;
}

string hw_Button::action()
{
	return baction;
}
string hw_Button::isPressedChecker()
{
	string s= string("((") + PORT + string("& (1<<") + PIN +string(")) == ");
	if( active==high )
		s+=string( "1<<")+PIN+string(")");
	else
		s+=string("0")+string(")");

	return s;
}

void hw_Button::display(){
	cout<<"Button\n------------------------------\n"
		<<name()<<endl
		<<P<<endl
		<<DDR<<endl
		<<PIN<<endl
		<<PORT<<endl
		<<active
		<<"\n-----------------------------------\n";

}



hw_Button::~hw_Button(void)
{
}

