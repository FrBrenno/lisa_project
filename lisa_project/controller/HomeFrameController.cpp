#include "HomeFrameController.h"
#include "../view/InstrumentSelectionDialog.h"
#include "../EventDispatcher.h"

HomeFrameController::HomeFrameController(MyApp* app, bool is_wfs_connected) : BaseController(app, is_wfs_connected)
{
	if (!is_wfs_connected) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent("InstrumentSelection");

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

void HomeFrameController::onCameraSettings(wxWindow* parent)
{
	Event cameraSettingsSelectionEvent("CameraSettingsSelection");

	EventDispatcher::Instance().PublishEvent(cameraSettingsSelectionEvent);
}

void HomeFrameController::onCapture(wxWindow* parent)
{
	// Save the last image of the camera
}
