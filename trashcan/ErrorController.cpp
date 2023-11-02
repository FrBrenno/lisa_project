#include "ErrorController.h"

void ErrorController::setErrorCode(const int code)
{
	this->code = code;
	WFS_error_message(VI_NULL, code, this->description);
}

void ErrorController::setErrorMessage(const std::string message)
{
	this->message = message;
}

void ErrorController::handleError()
{
	wxMessageBox(this->message, "Error", wxOK | wxICON_ERROR);
}
