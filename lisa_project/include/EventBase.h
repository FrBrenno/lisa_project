#pragma once

/**
 * @class EventBase.
 * @brief Base class for events.
 * @details This class is used to define the interface for events.
 */
class EventBase
{
public:
	virtual std::string getName() const = 0;
	virtual ~EventBase() {}
};
