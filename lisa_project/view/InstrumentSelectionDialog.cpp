#include "InstrumentSelectionDialog.h"

InstrumentSelectionDialog::InstrumentSelectionDialog(wxWindow* parent, IInstrumentViewListener* listener):
    wxDialog(parent, wxID_ANY, "LISA - PCV: Select Instrument")
{
    // Attributes setting
    this->parent = parent;
    this->listener = listener;

    //=== View Construction ===//

    this->panel = new wxPanel(this, wxID_ANY);
    this->panelSizer = new wxBoxSizer(wxVERTICAL);
    this->instrumentList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(300, -1), 0, NULL, wxLB_SINGLE);
    panelSizer->Add(instrumentList, 1, wxEXPAND | wxALL, 5);

    // Ok Button
    wxButton* okButton = new wxButton(panel, wxID_ANY, "OK");
    Bind(wxEVT_BUTTON, &InstrumentSelectionDialog::OnOK, this, okButton->GetId());
    panelSizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    // Close Button
    Bind(wxEVT_CLOSE_WINDOW, &InstrumentSelectionDialog::OnClose, this);

    panel->SetSizerAndFit(panelSizer);

    // Center the panel in the dialog
    this->mainSizer = new wxBoxSizer(wxHORIZONTAL);
    mainSizer->Add(panel, 1, wxALIGN_CENTER | wxALL, 10);
    SetSizerAndFit(mainSizer);

    CenterOnScreen();

}

void InstrumentSelectionDialog::ShowSelectionDialog()
{
    this->instrumentList->Clear();
    listener->populateInstrumentList(this->instrumentList);
    this->ShowModal();
}



void InstrumentSelectionDialog::OnOK(wxCommandEvent& event)
{
    int selectedIndex = this->instrumentList->GetSelection();
    listener->onInstrumentSelected(selectedIndex);
    this->EndModal(wxID_OK);
}

void InstrumentSelectionDialog::OnClose(wxCloseEvent& event)
{
	listener->onClose();
    this->EndModal(wxID_CANCEL);
}

