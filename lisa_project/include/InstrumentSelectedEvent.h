#pragma once
#include "Event.h"
#include "Instrument.h"

/**
 * @class InstrumentSelectedEvent.
 * @brief Event that is triggered when an instrument is selected.
 * 
 */
class InstrumentSelectedEvent : public Event<Instrument>
{
public:
	InstrumentSelectedEvent(Instrument* instrument) : Event("InstrumentSelected", instrument) {};
};
