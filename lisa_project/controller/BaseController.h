#pragma once

#include "wx/wx.h"
#include <string>


class BaseController{
protected:
	bool is_wfs_connected;
	/**
		 * Handles error messages.
		 *
		 * @param code Error code
		 * @param message Developer error message
		 */
	void handleError(int code, std::string message);

public:

	BaseController(bool is_wfs_connected);
	
	virtual void onOK();
	virtual void onClose();

	bool isWfsConnected() const;
};
