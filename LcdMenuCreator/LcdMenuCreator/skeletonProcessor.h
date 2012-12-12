#pragma once
#include <string>
#include <iostream>

#include "hw_Inputs.h"

using namespace std;

extern hw_Inputs *inputsPtr;

class skeletonProcessor
{
	void loopOverLine(string &l,string templ, string actionString);

public:
	string processed;

	skeletonProcessor(void);
	~skeletonProcessor(void);
};

