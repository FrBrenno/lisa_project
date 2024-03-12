#pragma once
#include <lib/thorlabs_api/visatype.h>
#include "view/HomeFrame.h"

class MyAppInterface
{
public:
	virtual ~MyAppInterface() {};
	virtual void check_api_connection() = 0;
	virtual ViSession getInstrumentHandle() = 0;
	virtual HomeFrame* getHomeFrame() = 0;
};
