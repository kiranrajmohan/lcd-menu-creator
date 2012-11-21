#include "PageCreator.h"


PageCreator::PageCreator(void)
{
}

PageCreator::PageCreator(xml_node n)
{
	name=string( n.attribute("name").as_string() );
	num=0;
	for( xml_node::iterator it=n.begin(); it!=n.end(); ++it, num++)
	{
		lines.push_back( Line( *it, num) );
	}
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
