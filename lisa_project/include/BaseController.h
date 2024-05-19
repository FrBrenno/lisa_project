#pragma once

#include "wx/wx.h"
#include "MyAppInterface.h"
#include "IApiService.h"
#include <string>


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
	
	virtual void onOK();
	virtual void onClose();

};
