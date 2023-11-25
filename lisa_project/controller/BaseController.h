#pragma once

#include "wx/wx.h"
#include <string>

class MyApp;

class BaseController{
protected:
	MyApp* app;
	bool is_wfs_connected;
public:
	BaseController(MyApp* app, bool is_wfs_connected);
	/**
	 * Handles when the user closes the view.
	 *
	 */
	virtual void onClose() {
		return;
	};
	/**
		 * Handles error messages.
		 *
		 * @param code Error code
		 * @param message Developer error message
		 */
	void handleError(int code, std::string message);

	void check_api_connection();
};
