#include "BaseController.h"
#include "WFS.h"
#include "../MyApp.h"
#include "../EventDispatcher.h"

BaseController::BaseController(MyAppInterface* main, bool is_wfs_connected) {
	this->app = main;
	this->is_wfs_connected = is_wfs_connected;

	EventDispatcher::Instance().SubscribeToEvent("ApiStatusChange", [this](Event event) {
		this->setWfsConnected(*(bool*)event.getData());
	});
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
		strcpy(description, "");
	}	
	wxMessageBox(wxString::Format("%s\n\t%s", message, description), "PCV - Error", wxOK | wxICON_ERROR);
}

bool BaseController::isWfsConnected() const {
	return this->is_wfs_connected;
}

void BaseController::setWfsConnected(bool isWfsConnected) {
	this->is_wfs_connected = isWfsConnected;
}

void BaseController::onOK() {
	return;
}

void BaseController::onClose() {
	return;
}
