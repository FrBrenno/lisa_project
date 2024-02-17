#include "InstrumentSelectionDialog.h"

InstrumentSelectionDialog::InstrumentSelectionDialog(wxWindow* parent, InstrumentController* controller): wxDialog(parent, wxID_ANY, "LISA - PCV: Select Instrument")
{
    // Attributes setting
    this->parent = parent;
    this->controller = controller;

    //=== View Construction ===//

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxListBox* instrumentList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, -1), 0, NULL, wxLB_SINGLE);
    panelSizer->Add(instrumentList, 1, wxEXPAND | wxALL, 5);

    // Populate Instrument List
    controller->populateInstrumentList(instrumentList);

    if (instrumentList->GetCount() == 1)
    {
        controller->onInstrumentSelected(0);
        this->Destroy();
    }
    // Show popup if more than one instruments is available
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

    CenterOnScreen();
}

void InstrumentSelectionDialog::OnOK(wxCommandEvent& event)
{
    // FIXME: The selectedIndex is not the index of the element selected in the list.
    int selectedIndex = event.GetSelection();
    controller->onInstrumentSelected(selectedIndex);
    this->Destroy();
}

void InstrumentSelectionDialog::OnClose(wxCloseEvent& event)
{
	controller->onClose();
    this->Destroy();
}

