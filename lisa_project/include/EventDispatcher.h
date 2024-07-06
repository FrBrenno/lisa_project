#pragma once
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "EventBase.h"

/**
  @class EventDispatcher
  @brief This class is a singleton that handles the publishing and subscribing to events. 
  @details Useful to manage intercontroller communication.
 */
class EventDispatcher {
    EventDispatcher() {}  // Private constructor
    /**
     * @brief Map of subscribers and their callbacks.
     * 
     */
    std::unordered_map<std::type_index, std::function<void(const EventBase&)>> subscribers; // Map of subscribers and their callbacks

public:
    /**
     * @brief Get the instance of the EventDispatcher.
     * 
     * @return EventDispatcher& 
     */
    static EventDispatcher& Instance() {
        static EventDispatcher instance;
        return instance;
    }

    /**
     * @brief Publish an event.
     * 
     * @tparam T Type of the event.
     * @param event Event to be published.
     */
    template<typename T>
    void PublishEvent(const T& event) {
        auto it = subscribers.find(std::type_index(typeid(event)));
        if (it != subscribers.end()) {
            it->second(event);
        }
    }

    /**
     * @brief Subscribe to an event.
     * 
     * @tparam T Type of the event.
     * @param callback Callback function to be called when the event is published.
     */
    template<typename T>
    void SubscribeToEvent(std::function<void(const T&)> callback) {
        subscribers[std::type_index(typeid(T))] = [=](const EventBase& baseEvent) {
            const T& event = dynamic_cast<const T&>(baseEvent);
            callback(event);
            };
    }
};