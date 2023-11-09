#pragma once
#include <string>
#include <functional>
#include <vector>
#include "Event.h"

/**
  @class EventDispatcher
  @brief This class is a singleton that handles the publishing and subscribing to events. 
  @details Useful to manage intercontroller communication.
 */
class EventDispatcher {
    EventDispatcher() {}  // Private constructor
    std::vector<std::pair<std::string, std::function<void(const Event&)>>> subscribers; // List of subscribers and their callbacks

public:
    static EventDispatcher& Instance() {
        static EventDispatcher instance;
        return instance;
    }

    /**
     * Publishes an event. This will call all the callbacks of the subscribers to this event.
     * @param event Event to publish
     */
    void PublishEvent(const Event& event); 
    /**
     * Allow an object to subscribe to an event. Whenever this event is published, the callback will be called.
     * 
     * @param eventName Event to subscribe to
     * @param callback Callback to be called when the event is published
     */
    void SubscribeToEvent(const std::string& eventName, std::function<void(const Event&)> callback);
};