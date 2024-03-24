#pragma once

class EventBase
{
public:
	virtual std::string getName() const = 0;
	virtual ~EventBase() {}
};
