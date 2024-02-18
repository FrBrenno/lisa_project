#pragma once
#include <lib/thorlabs_api/visatype.h>

class MyAppInterface
{
public:
	virtual ~MyAppInterface() {};
	virtual void check_api_connection() = 0;
	virtual ViSession getInstrumentHandle() = 0;
};
