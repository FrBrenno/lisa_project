#pragma once
#include <string>
#include <functional>
#include <vector>
#include "Event.h"

class EventDispatcher {
    EventDispatcher() {}  // Private constructor
    std::vector<std::pair<std::string, std::function<void(const Event&)>>> subscribers;

public:
    static EventDispatcher& Instance() {
        static EventDispatcher instance;
        return instance;
    }

    void PublishEvent(const Event& event);
    void SubscribeToEvent(const std::string& eventName, std::function<void(const Event&)> callback);
};