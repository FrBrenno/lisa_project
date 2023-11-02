#pragma once
#include <string>
#include "WFS.h"
#include "wx/wx.h"

class ErrorController{
	int code;
	std::string message;
	ViChar description[WFS_ERR_DESCR_BUFFER_SIZE];

public:
	void setErrorCode(const int code);
	void setErrorMessage(const std::string message);

	void handleError();
};
