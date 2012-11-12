#include "ConfigManager.h"


ConfigManager::ConfigManager(void)
{
}

ConfigManager::ConfigManager( xml_node n)
{

	activeLineIndicator=n.child("LineIndicator").attribute("active").value();
	lineIndicator=n.child("LineIndicator").attribute("default").value();
	maxLines=n.child("maxLines").text().as_int();
	maxChar=n.child("maxChar").text().as_int();
}

void ConfigManager::display()
{
	cout<<lineIndicator<<"  "<< activeLineIndicator<<endl
		<<"maxLines="<<maxLines<<endl<<"maxChar="<<maxChar<<endl<<endl;
}

ConfigManager::~ConfigManager(void)
{
}
