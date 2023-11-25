#include "HomeFrameController.h"
#include "../view/InstrumentSelectionDialog.h"
#include "../EventDispatcher.h"

HomeFrameController::HomeFrameController(MyApp* app, bool is_wfs_connected) : BaseController(app, is_wfs_connected)
{
	isApiConnected();
}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent;
	instrumentSelectionEvent.name = "InstrumentSelection";

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

void HomeFrameController::onCameraSettings(wxWindow* parent)
{
	Event cameraSettingsSelectionEvent;
	cameraSettingsSelectionEvent.name = "CameraSettingsSelection";

	EventDispatcher::Instance().PublishEvent(cameraSettingsSelectionEvent);
}

