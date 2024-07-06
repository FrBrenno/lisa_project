#pragma once
#include "Event.h"

/**
 * @brief Event used to notify the exit of the application.
 * 
 */
class ExitEvent : public Event<void> 
{
public:
	ExitEvent() : Event<void>("ExitEvent") {}
};
