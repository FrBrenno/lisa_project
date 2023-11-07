#pragma once
#include <wx/wx.h>
#include "MlaController.h"

class MlaSelectionDialog : public wxDialog {
	wxWindow* parent;
	MlaController* listener;
public:
	MlaSelectionDialog(wxWindow* parent, MlaController* listener);

	void OnOK(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};
