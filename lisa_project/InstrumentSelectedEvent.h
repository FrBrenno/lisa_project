#pragma once
#include "Event.h"
#include "model/Instrument.h"

class InstrumentSelectedEvent : public Event<Instrument>
{
public:
	InstrumentSelectedEvent(Instrument* instrument) : Event("InstrumentSelected", instrument) {};
};
