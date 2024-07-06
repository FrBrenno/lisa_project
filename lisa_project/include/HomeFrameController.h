#pragma once
#include "wx/wx.h"
#include "BaseController.h"
#include "IHomeFrameListener.h"

/**
 * @class HomeFrameController.
 * @brief This controller manages HomeFrame view responsible for the main window of the software.
 */
class HomeFrameController : public BaseController, public IHomeFrameListener{
public:
	HomeFrameController(MyAppInterface* main, IApiService* wfsApiService);
	/**
	 * @brief Connect to the Thorlabs WaveFront Sensor API.
	 * 
	 * This method is called when the user clicks on the "Connect to API" button.
	 */
	void onConnectAPI() override;

};
