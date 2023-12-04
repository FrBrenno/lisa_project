#pragma once

#include "wx/wx.h"
#include "../MyAppInterface.h"
#include <string>


class BaseController{
protected:
	MyAppInterface* app;
	bool is_wfs_connected;
	/**
		 * Handles error messages.
		 *
		 * @param code Error code
		 * @param message Developer error message
		 */
	void handleError(int code, std::string message);

public:

	BaseController(MyAppInterface* main, bool is_wfs_connected);
	
	virtual void onOK();
	virtual void onClose();

	bool isWfsConnected() const;
	void setWfsConnected(bool isWfsConnected);
};
