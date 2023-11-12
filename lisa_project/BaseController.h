#pragma once

#include "wx/wx.h"
#include <string>

class BaseController{

public:
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
};
