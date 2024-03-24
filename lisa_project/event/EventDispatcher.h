#pragma once
#include <string>
#include <functional>
#include <vector>
#include "EventBase.h"
#include <unordered_map>
#include <typeindex>

/**
  @class EventDispatcher
  @brief This class is a singleton that handles the publishing and subscribing to events. 
  @details Useful to manage intercontroller communication.
 */
class EventDispatcher {
    EventDispatcher() {}  // Private constructor
    std::unordered_map<std::type_index, std::function<void(const EventBase&)>> subscribers; // Map of subscribers and their callbacks

public:
    static EventDispatcher& Instance() {
        static EventDispatcher instance;
        return instance;
    }

    template<typename T>
    void PublishEvent(const T& event) {
        auto it = subscribers.find(std::type_index(typeid(event)));
        if (it != subscribers.end()) {
            it->second(event);
        }
    }

    template<typename T>
    void SubscribeToEvent(std::function<void(const T&)> callback) {
        subscribers[std::type_index(typeid(T))] = [=](const EventBase& baseEvent) {
            const T& event = dynamic_cast<const T&>(baseEvent);
            callback(event);
            };
    }
};