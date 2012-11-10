#pragma once
#include <string>
#include "pugixml.hpp"

using namespace std;
using namespace pugi;


class hw_Button
{

private:

	enum activeState{ low, high };
	string		bname,
				P,
				DDR,
				PIN,
				PORT;
	activeState active;

public:
	hw_Button(void);
	hw_Button( string _name, string p, string ddr, string pin, string port, int _active);
	hw_Button( xml_node button );

	//setters
	void assign( string _name, string p, string ddr, string pin, string port, int _active);

	//getters
	string name();

	//generators
	string isPressedChecker();


	//debug methods
	void display();

	~hw_Button(void);
};

