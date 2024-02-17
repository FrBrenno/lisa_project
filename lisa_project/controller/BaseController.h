#pragma once

#include "wx/wx.h"
#include "../MyAppInterface.h"
#include <string>
#include <wfsApiService.h>


class BaseController{
protected:
	MyAppInterface* app;
	WfsApiService* wfsApiService;
	/**
		 * Handles error messages.
		 *
		 * @param code Error code
		 * @param message Developer error message
		 */
	void handleError(int code, std::string message);

public:

	BaseController(MyAppInterface* main, WfsApiService* wfsApiService);
	
	virtual void onOK();
	virtual void onClose();

	bool isWfsConnected() const;
};
