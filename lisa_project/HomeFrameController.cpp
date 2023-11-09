#include "HomeFrameController.h"
#include "InstrumentSelectionDialog.h"
#include "EventDispatcher.h"

HomeFrameController::HomeFrameController()
{}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent;
	instrumentSelectionEvent.name = "InstrumentSelection";

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

