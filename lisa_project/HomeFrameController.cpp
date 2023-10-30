#include "HomeFrameController.h"
#include "WFS.h"
HomeFrameController::HomeFrameController(wxApp* main) {
	this->main = main;
}

void HomeFrameController::selectInstrument(){
	wxMessageBox("Select Instrument");
}

void HomeFrameController::reviseDrive(){
	if (err = WFS)
}
