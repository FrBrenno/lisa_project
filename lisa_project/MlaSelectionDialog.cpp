#include "MlaSelectionDialog.h"

MlaSelectionDialog::MlaSelectionDialog(wxWindow* parent, MlaController* listener) : wxDialog(parent, wxID_ANY, "Select MLA", wxDefaultPosition, wxSize(300, 200)) {
	// Attributes setting
	this->parent = parent;
	this->listener = listener;

	//=== View Construction ===//

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
	wxListBox* mlaList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, -1), 0, NULL, wxLB_SINGLE);
	panelSizer->Add(mlaList, 1, wxEXPAND | wxALL, 5);

	// Populate Instrument List
	listener->populateMlaList(mlaList);

	// Show popup if more than one instrument is available
	if (mlaList->GetCount() > 1)
	{
		// Ok Button
		wxButton* okButton = new wxButton(panel, wxID_ANY, "OK");
		Bind(wxEVT_BUTTON, &MlaSelectionDialog::OnOK, this, okButton->GetId());
		panelSizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

		// Close Button
		Bind(wxEVT_CLOSE_WINDOW, &MlaSelectionDialog::OnClose, this);

		panel->SetSizerAndFit(panelSizer);
		// Center the panel in the dialog
		wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
		mainSizer->Add(panel, 1, wxALIGN_CENTER | wxALL, 10);
		SetSizerAndFit(mainSizer);
	}
	else
	{
		this->Destroy();
	}
	CenterOnScreen();
}

void MlaSelectionDialog::OnOK(wxCommandEvent& event)
{
	// FIXME: It should get the index of the element selected on the list. I guess this is getting a 0 every time.
	int selectedIndex = event.GetSelection();
	listener->onMlaSelected(selectedIndex);
	this->Destroy();
}

void MlaSelectionDialog::OnClose(wxCloseEvent& event)
{
	listener->onClose();
	this->Destroy();
}
