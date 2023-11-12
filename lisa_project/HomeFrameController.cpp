#include "HomeFrameController.h"
#include "InstrumentSelectionDialog.h"
#include "EventDispatcher.h"

HomeFrameController::HomeFrameController(bool is_wfs_connected) : BaseController(is_wfs_connected)
{}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent;
	instrumentSelectionEvent.name = "InstrumentSelection";

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

