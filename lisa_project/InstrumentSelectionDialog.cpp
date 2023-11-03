#include "InstrumentSelectionDialog.h"

InstrumentSelectionDialog::InstrumentSelectionDialog(wxWindow* parent): wxDialog(parent, wxID_ANY, "Select Instrument")
{
    this->parent = parent;

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

    // Instrument List
    wxListBox* instrumentList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, -1), 0, NULL, wxLB_SINGLE);
    panelSizer->Add(instrumentList, 1, wxEXPAND | wxALL, 5);

    // Populate Instrument List
    //listener->populateInstrumentList(instrumentList);
    instrumentList->Append("Hello"); //DEBUG
    instrumentList->Append("World"); //DEBUG

    // Show popup if one or more instruments are available
    if (instrumentList->GetCount() > 0)
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

void InstrumentSelectionDialog::setListener(InstrumentController* listener)
{
	this->listener = listener;
}

void InstrumentSelectionDialog::OnOK(wxCommandEvent& event)
{
    int selectedIndex = event.GetSelection();
    listener->onInstrumentSelected(selectedIndex);
}

void InstrumentSelectionDialog::OnClose(wxCloseEvent& event)
{
	listener->onClose();
    this->Destroy();
}

