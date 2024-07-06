#pragma once
#include <wx/wx.h>

/**
 * @class IHomeFrameListener.
 * @brief Interface for the HomeFrame listener.
 * 
 * This interface defines the methods that must be implemented by the HomeFrame listener.
 */
class IHomeFrameListener
{
public:
	/**
	 * @brief Connect to the Thorlabs WaveFront Sensor API.
	 * 
	 * This method is called when the user clicks on the "Connect to API" button.
	 */
	virtual void onConnectAPI() = 0;
};
