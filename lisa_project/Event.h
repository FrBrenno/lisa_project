#pragma once
#include <string>

/**
 * @struct Event.
 * @brief This class is an instance of an event.
 * @details It is possible to transmit data with the event by passing the pointer to it as attribute. 
 */
struct Event {
    /**
     * Event name.
     */
    std::string name; 
    /**
     * Pointer to data generate by the event.
     */
    void* data; 
};