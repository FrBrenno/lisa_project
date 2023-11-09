#include "InstrumentSelectionDialog.h"

InstrumentSelectionDialog::InstrumentSelectionDialog(wxWindow* parent, InstrumentController* listener): wxDialog(parent, wxID_ANY, "LISA - PCV: Select Instrument")
{
    // Attributes setting
    this->parent = parent;
    this->listener = listener;

    //=== View Construction ===//

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxListBox* instrumentList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, -1), 0, NULL, wxLB_SINGLE);
    panelSizer->Add(instrumentList, 1, wxEXPAND | wxALL, 5);

    // Populate Instrument List
    listener->populateInstrumentList(instrumentList);

    // Show popup if more than one instruments is available
    if (instrumentList->GetCount() > 1)
	{
        // Ok Button
        wxButton* okButton = new wxButton(panel, wxID_ANY, "OK");
        Bind(wxEVT_BUTTON, &InstrumentSelectionDialog::OnOK, this, okButton->GetId());
        panelSizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

        // Close Button
        Bind(wxEVT_CLOSE_WINDOW, &InstrumentSelectionDialog::OnClose, this);

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

void InstrumentSelectionDialog::OnOK(wxCommandEvent& event)
{
    // FIXME: The selectedIndex is not the index of the element selected in the list.
    int selectedIndex = event.GetSelection();
    listener->onInstrumentSelected(selectedIndex);
    this->Destroy();
}

void InstrumentSelectionDialog::OnClose(wxCloseEvent& event)
{
	listener->onClose();
    this->Destroy();
}

