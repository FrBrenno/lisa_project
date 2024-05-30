#pragma once
#include "thorlabs_api/visatype.h"
#include "HomeFrame.h"

class MyAppInterface
{
public:
	virtual ~MyAppInterface() {};
	virtual void check_api_connection() = 0;
	virtual ViSession getInstrumentHandle() = 0;
	virtual HomeFrame* getHomeFrame() = 0;
};
