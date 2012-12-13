#include "ConfigManager.h"

int ConfigManager::maxLines=0;
int ConfigManager::maxChar=0;
int ConfigManager::maxLineIndicatorLength=0;
string ConfigManager::activeLineIndicator=string("");
string ConfigManager::lineIndicator=string("");
ConfigManager::ConfigManager(void)
{
}

ConfigManager::ConfigManager( xml_node n)
{
	activeLineIndicator=n.child("LineIndicator").attribute("active").value();
	lineIndicator=n.child("LineIndicator").attribute("default").value();
	int l= activeLineIndicator.length() - lineIndicator.length();

	if( l>0 ){ //active is longer
		for( int i=0;i<l;i++)
			lineIndicator+=" ";
	}else{
		for( int i=0;i<l;i++)
			lineIndicator+=" ";
	}
	maxLines=n.child("maxLines").text().as_int();
	maxChar=n.child("maxChar").text().as_int();
	if( activeLineIndicator.length() >  lineIndicator.length() ){
		maxLineIndicatorLength=activeLineIndicator.length();
	}else{
		maxLineIndicatorLength=lineIndicator.length();
	}
}

void ConfigManager::display()
{
	cout<<lineIndicator<<"  "<< activeLineIndicator<<endl
		<<"maxLines="<<maxLines<<endl<<"maxChar="<<maxChar<<endl<<endl;
}

ConfigManager::~ConfigManager(void)
{
}
