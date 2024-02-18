#include "BaseController.h"
#include "lib/thorlabs_api/WFS.h"
#include "../MyApp.h"
#include "../EventDispatcher.h"

BaseController::BaseController(MyAppInterface* main, WfsApiService* wfsApiService) {
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
		if (code == WFS_ERROR_NO_SENSOR_CONNECTED)
		{
			EventDispatcher::Instance().PublishEvent(Event("ApiStatusChange", new bool(false)));
		}
	}
	else
	{
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

bool BaseController::isWfsConnected() const
{
	return this->wfsApiService->isApiConnectionActive();
}
