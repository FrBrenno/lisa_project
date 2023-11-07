#pragma once
#include "wx/wx.h"
#include "Instrument.h"
#include "Event.h"

class InstrumentController{
	Instrument* selectedInstrument;
	ViInt32 instrumentCount;
	ViInt32 err;

	void HandleInstrumentSelection(const Event& event);
	void HandleMlaSelected(const Event& event);

public:
	InstrumentController();

	std::string getInstrumentName();

	void populateInstrumentList(wxListBox* list);
	void onInstrumentSelected(int selectedIndex);
	void initInstrument(ViRsrc resourceName);
	void reviseDrive();
	void cameraConfiguration();
	void mlaConfiguration();
	void onClose();	

	void handleError(int code, std::string message);
};
