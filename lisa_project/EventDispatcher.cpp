#include "EventDispatcher.h"

void EventDispatcher::PublishEvent(const Event& event)
{
	for (auto& subscriber : subscribers)
	{
		if (subscriber.first == event.name) {
			subscriber.second(event);
		}
	}
}

void EventDispatcher::SubscribeToEvent(const std::string& eventName, std::function<void(const Event&)> callback)
{
	subscribers.push_back({ eventName, callback });
}
