#pragma once
#include "Event.h"

/**
 * @class InstrumentSelectionEvent.
 * @brief Event that is triggered when user wants to select a new instrument.
 * 
 */
class InstrumentSelectionEvent : public  Event<void>
{
public:
	InstrumentSelectionEvent() : Event("InstrumentSelection") {};
};
