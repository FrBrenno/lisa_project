#pragma once
#include "wx/wx.h"
#include "BaseController.h"
#include "Instrument.h"

class InstrumentController : public BaseController {
	Instrument* selectedInstrument;

public:
	InstrumentController(wxApp* main);

	void PopulateInstrumentList(wxListBox* list);
	void OnInstrumentSelected(int selectedIndex);
	void OnClose();

	void reviseDrive(Instrument* instrument);

	void handleError(int code, std::string message);
};
