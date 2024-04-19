#pragma once
#include "Event.h"

class OnLoadImageEvent : public Event<void>
{
public:
	OnLoadImageEvent() : Event("OnLoadImage", nullptr) {};
};
