#include "MlaSelectionDialog.h"

MlaSelectionDialog::MlaSelectionDialog(wxWindow* parent, MlaController* listener) : wxDialog(parent, wxID_ANY, "Select MLA", wxDefaultPosition, wxSize(300, 200)) {
	this->parent = parent;
	this->listener = listener;

	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

	// MLA List
	wxListBox* mlaList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, -1), 0, NULL, wxLB_SINGLE);
	panelSizer->Add(mlaList, 1, wxEXPAND | wxALL, 5);

	// Populate Instrument List
	listener->populateMlaList(mlaList);

	// Show popup if one or more instruments are available
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
}

void MlaSelectionDialog::OnOK(wxCommandEvent& event)
{
	int selectedIndex = event.GetSelection();
	listener->onMlaSelected(selectedIndex);
	this->Destroy();
}

void MlaSelectionDialog::OnClose(wxCloseEvent& event)
{
	listener->onClose();
	this->Destroy();
}
