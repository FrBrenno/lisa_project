#pragma once
#include "Event.h"

class ExitEvent : public Event<void> 
{
public:
	ExitEvent() : Event<void>("ExitEvent") {}
};
