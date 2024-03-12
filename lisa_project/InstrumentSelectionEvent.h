#pragma once
#include "Event.h"

class InstrumentSelectionEvent : public  Event<void>
{
public:
	InstrumentSelectionEvent() : Event("InstrumentSelection") {};
};
