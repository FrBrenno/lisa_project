#pragma once
#include "Event.h"
#include "Instrument.h"

class InstrumentSelectedEvent : public Event<Instrument>
{
public:
	InstrumentSelectedEvent(Instrument* instrument) : Event("InstrumentSelected", instrument) {};
};
