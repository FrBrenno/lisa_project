#include "CameraSettingsDialog.h"
#include "EventDispatcher.h"

CameraSettingsDialog::CameraSettingsDialog(wxWindow* parent, CameraSettingsController* controller)
{
	this->parent = parent;
	this->listener = controller;

	//=== View Construction ===//
    //wxListBox* resolutionListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxLB_SINGLE);
    wxTextCtrl* nbImageReadingCtrl = new wxTextCtrl(this, wxID_ANY);
    wxTextCtrl* exposureTimeCtrl = new wxTextCtrl(this, wxID_ANY);
    wxTextCtrl* noiseCutLevelCtrl = new wxTextCtrl(this, wxID_ANY);
    wxTextCtrl* gainCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format(wxT("%.2f"), 1.00));
    wxTextCtrl* blackLevelCtrl = new wxTextCtrl(this, wxID_ANY);
    wxButton* autoExposureButton = new wxButton(this, wxID_ANY, wxT("Auto"));
    wxButton* autoNoiseCutButton = new wxButton(this, wxID_ANY, wxT("Auto"));
    wxButton* autoBlackLevelButton = new wxButton(this, wxID_ANY, wxT("Auto"));
    wxButton* setDefaultButton = new wxButton(this, wxID_ANY, wxT("Set Default"));
    wxButton* cancelButton = new wxButton(this, wxID_ANY, wxT("Cancel"));
    wxButton* okButton = new wxButton(this, wxID_ANY, wxT("OK"));

    // Create sizers
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);

    // Add controls to sizers
    vbox->Add(new wxStaticText(this, wxID_ANY, wxT("Camera Resolution:")), 0, wxALIGN_LEFT | wxTOP, 10);
    //vbox->Add(resolutionListBox, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(this, wxID_ANY, wxT("Number of Image Reading:")), 0, wxALIGN_LEFT | wxTOP, 10);
    vbox->Add(nbImageReadingCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(this, wxID_ANY, wxT("Exposure Time:")), 0, wxALIGN_LEFT | wxTOP, 10);
    vbox->Add(exposureTimeCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(autoExposureButton, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(this, wxID_ANY, wxT("Noise Cut Level:")), 0, wxALIGN_LEFT | wxTOP, 10);
    vbox->Add(noiseCutLevelCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(autoNoiseCutButton, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(this, wxID_ANY, wxT("Gain:")), 0, wxALIGN_LEFT | wxTOP, 10);
    vbox->Add(gainCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(new wxStaticText(this, wxID_ANY, wxT("Black Level:")), 0, wxALIGN_LEFT | wxTOP, 10);
    vbox->Add(blackLevelCtrl, 0, wxEXPAND | wxALL, 5);
    vbox->Add(autoBlackLevelButton, 0, wxEXPAND | wxALL, 5);
    vbox->Add(setDefaultButton, 0, wxEXPAND | wxALL, 5);

    hbox->Add(cancelButton, 0, wxEXPAND | wxALL, 5);
    hbox->Add(okButton, 0, wxEXPAND | wxALL, 5);

    vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    // Set sizer for the panel
    SetSizer(vbox);
}
