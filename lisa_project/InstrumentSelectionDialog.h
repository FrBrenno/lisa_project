#pragma once
#include <wx/wx.h>
#include "InstrumentController.h"

class InstrumentSelectionDialog: public wxDialog{
	wxWindow* parent;
	InstrumentController* listener;

public:	
	InstrumentSelectionDialog(wxWindow* parent);

	void setListener(InstrumentController* listener);

	void OnOK(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};
