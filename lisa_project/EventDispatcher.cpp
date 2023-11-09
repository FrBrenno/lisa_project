#include "EventDispatcher.h"

void EventDispatcher::PublishEvent(const Event& event)
{
	for (auto& subscriber : subscribers)
	{
		// If the subscriber is subscribed to the event, call the callback
		if (subscriber.first == event.name) {
			subscriber.second(event);
		}
	}
}

void EventDispatcher::SubscribeToEvent(const std::string& eventName, std::function<void(const Event&)> callback)
{
	// Add the subscriber and its event to the list of subscribers
	subscribers.push_back({ eventName, callback });
}
