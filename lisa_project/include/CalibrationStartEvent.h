#pragma once
#include "Event.h"

/**
 * @brief Event used to notify the start of the calibration proces, when user click on "Start Calibration".
 * 
 */
class CalibrationStartEvent : public Event<void>
{
public:
	CalibrationStartEvent() : Event<void>("CalibrationStart") {}
};
