#pragma once
#include "Event.h"

class MlaSelectionEvent : public Event<void>
{
public:
	MlaSelectionEvent() : Event<void>("MlaSelectionEvent") {}
};
