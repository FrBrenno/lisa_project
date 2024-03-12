#include "BaseController.h"
#include "lib/thorlabs_api/WFS.h"
#include "../MyApp.h"

BaseController::BaseController(MyAppInterface* main, IApiService* wfsApiService) {
	this->app = main;
	this->wfsApiService = wfsApiService;
}

void BaseController::handleError(int code, std::string message){
	char description[WFS_ERR_DESCR_BUFFER_SIZE];

	if (!code) return;

	// Get error string
	if (code != -1)
	{
		WFS_error_message(VI_NULL, code, description);
	}
	else
	{
		// If code is -1, then it is not a WFS error
		strcpy_s(description, "");
	}	
	wxMessageBox(wxString::Format("%s\n\t%s", message, description), "PCV - Error", wxOK | wxICON_ERROR);
}

void BaseController::onOK() {
	return;
}

void BaseController::onClose() {
	return;
}

