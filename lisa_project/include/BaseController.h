#pragma once

#include "wx/wx.h"
#include "MyAppInterface.h"
#include "IApiService.h"
#include <string>

/**
 * @class BaseController.
 * @brief Base class for all controllers.
 * @details This class is responsible for handling error messages and contains the main application and API service.
 */
class BaseController{
protected:
	MyAppInterface* app;
	IApiService* wfsApiService;
	/**
		 * Handles error messages.
		 *
		 * @param code Error code
		 * @param message Developer error message
		 */
	void handleError(int code, std::string message);

public:

	BaseController(MyAppInterface* main, IApiService* wfsApiService);
	
	/**
	 * Handles the OK button.
	**/
	virtual void onOK();
	/**
	* Handles the Cancel button.
	*/
	virtual void onClose();

};
