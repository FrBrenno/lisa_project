#pragma once
#include <string>
#include "EventBase.h"

/**
 * @class Event.
 * @brief This class is an instance of an event.
 * @details It is possible to transmit data with the event by passing the pointer to it as attribute. 
 */
template <typename T>
class Event : public EventBase {
    /**
     * Event name.
     */
    std::string name; 
    /**
     * Pointer to data generate by the event.
     */
    T* data; 
public:
    /**
    * @brief Constructor.
    ** @param name Event name.
    ** @param data Pointer to data generate by the event.
    **/
    Event(std::string name, T* data = nullptr) : name(name), data(data) {}
    /**
    * @brief Getter for event name.
    ** @return Event name.
    **/
    std::string getName() const { return name; };
    /**
    * @brief Getter for event data.
    ** @return Pointer to data generate by the event.
    **/
    T* getData() const { return data; };
};




