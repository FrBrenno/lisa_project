#include "HomeFrameController.h"
#include "InstrumentSelectionDialog.h"
#include "EventDispatcher.h"

HomeFrameController::HomeFrameController(bool is_wfs_connected) : BaseController(is_wfs_connected)
{
	if (!is_wfs_connected) {
		this->handleError(-1, "No WFS connected");
	}
}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent;
	instrumentSelectionEvent.name = "InstrumentSelection";

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

void HomeFrameController::onCameraSettings(wxWindow* parent)
{
	Event settingsSelectionEvent;
	settingsSelectionEvent.name = "SettingsSelection";

	EventDispatcher::Instance().PublishEvent(settingsSelectionEvent);
}

