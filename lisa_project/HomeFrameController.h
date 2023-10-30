#pragma once
#include <wx/wx.h>
#include "Instrument.h"

class HomeFrameController{
private:
	wxApp* main;
public:
	HomeFrameController(wxApp *main);
	Instrument* selectInstrument();
	void reviseDrive(Instrument* instrument);
};
