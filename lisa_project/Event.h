#pragma once
#include <string>

/**
 * @class Event.
 * @brief This class is an instance of an event.
 * @details It is possible to transmit data with the event by passing the pointer to it as attribute. 
 */
class Event {
    /**
     * Event name.
     */
    std::string name; 
    /**
     * Pointer to data generate by the event.
     */
    void* data; 
public:
    /**
    * @brief Constructor.
    ** @param name Event name.
    ** @param data Pointer to data generate by the event.
    **/
    Event(std::string name, void* data = nullptr) : name(name), data(data) {}
    /**
    * @brief Getter for event name.
    ** @return Event name.
    **/
    std::string getName() const { return name; }
    /**
    * @brief Getter for event data.
    ** @return Pointer to data generate by the event.
    **/
    void* getData() const { return data; }
};




