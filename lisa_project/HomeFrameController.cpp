#include "HomeFrameController.h"
#include "InstrumentSelectionDialog.h"
#include "EventDispatcher.h"

HomeFrameController::HomeFrameController()
{
	EventDispatcher::Instance().SubscribeToEvent("InstrumentSelected", 
		[this](const Event& event) {
			handleInstrumentSelected(event);
		});
}

void HomeFrameController::onInstrumentSelection(wxWindow* parent) 
{
	Event instrumentSelectionEvent;
	instrumentSelectionEvent.name = "InstrumentSelection";

	EventDispatcher::Instance().PublishEvent(instrumentSelectionEvent);
}

void HomeFrameController::handleInstrumentSelected(const Event& event)
{
	// TODO: Handle the return value of the dialog
}
