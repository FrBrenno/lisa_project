#pragma once
#include "Event.h"

class CalibrationStartEvent : public Event<void>
{
public:
	CalibrationStartEvent() : Event<void>("CalibrationStart") {}
};
