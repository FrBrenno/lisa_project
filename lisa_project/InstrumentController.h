#pragma once
#include "wx/wx.h"
#include "Instrument.h"
#include "Event.h"

class InstrumentController{
	Instrument* selectedInstrument;
	ViInt32 instrumentCount;
	ViInt32 err;

	void HandleInstrumentSelection(const Event& event);

public:
	InstrumentController();

	std::string getInstrumentName();

	void reviseDrive(Instrument* instrument);
	void populateInstrumentList(wxListBox* list);
	void onInstrumentSelected(int selectedIndex);
	void initInstrument(ViRsrc resourceName);
	void onClose();	

	void handleError(int code, std::string message);
};
