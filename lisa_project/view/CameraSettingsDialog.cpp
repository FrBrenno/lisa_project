#include "CameraSettingsDialog.h"

CameraSettingsDialog::CameraSettingsDialog(wxWindow* parent, CameraSettingsController* controller)
	: wxDialog(parent, wxID_ANY, "Settings")
{
	this->parent = parent;
	this->controller = controller;

	//=== View Construction ===//
    wxListBox* resolutionListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxArrayString(), wxLB_SINGLE);
    wxTextCtrl* nbImageReadingCtrl = new wxTextCtrl(this, wxID_ANY);
    wxTextCtrl* exposureTimeCtrl = new wxTextCtrl(this, wxID_ANY);
    wxTextCtrl* noiseCutLevelCtrl = new wxTextCtrl(this, wxID_ANY);
    wxTextCtrl* gainCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format(wxT("%.2f"), 1.00));
    gainCtrl->Enable(false);
    wxTextCtrl* blackLevelCtrl = new wxTextCtrl(this, wxID_ANY);
    
    wxCheckBox* autoExposureButton = new wxCheckBox(this, wxID_ANY, wxT("Auto"));
    wxCheckBox* autoNoiseCutButton = new wxCheckBox(this, wxID_ANY, wxT("Auto"));
    wxCheckBox* autoBlackLevelButton = new wxCheckBox(this, wxID_ANY, wxT("Auto"));
    
    wxButton* setDefaultButton = new wxButton(this, wxID_ANY, wxT("Set Default"));
    wxButton* cancelButton = new wxButton(this, wxID_ANY, wxT("Cancel"));
    wxButton* okButton = new wxButton(this, wxID_ANY, wxT("OK"));

    // Create Layout
    wxFlexGridSizer* settingsSizer = new wxFlexGridSizer(2, 5, 5);
    settingsSizer->Add(new wxStaticText(this, wxID_ANY, "Camera Resolution"), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    settingsSizer->Add(resolutionListBox, 1, wxEXPAND);
    settingsSizer->Add(new wxStaticText(this, wxID_ANY, "Number of Images"), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    settingsSizer->Add(nbImageReadingCtrl, 1, wxEXPAND);
    settingsSizer->Add(new wxStaticText(this, wxID_ANY, "Gain"), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    settingsSizer->Add(gainCtrl, 1, wxEXPAND);

    wxFlexGridSizer* autoSettingsSizer = new wxFlexGridSizer(3, 5, 5);
    autoSettingsSizer->Add(new wxStaticText(this, wxID_ANY, "Exposure Time"), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    autoSettingsSizer->Add(exposureTimeCtrl, 1, wxEXPAND);
    autoSettingsSizer->Add(autoExposureButton);
    autoSettingsSizer->Add(new wxStaticText(this, wxID_ANY, "Noise Cut Level"), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    autoSettingsSizer->Add(noiseCutLevelCtrl, 1, wxEXPAND);
    autoSettingsSizer->Add(autoNoiseCutButton);
    autoSettingsSizer->Add(new wxStaticText(this, wxID_ANY, "Black Level"), 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    autoSettingsSizer->Add(blackLevelCtrl, 1, wxEXPAND);
    autoSettingsSizer->Add(autoBlackLevelButton);


    // Buttons layout
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    // Add buttons to the box sizer
    buttonSizer->AddStretchSpacer();
    buttonSizer->Add(setDefaultButton, 0, wxALIGN_RIGHT | wxRIGHT, 10);
    buttonSizer->Add(cancelButton, 0, wxALIGN_RIGHT | wxRIGHT, 10);
    buttonSizer->Add(okButton, 0, wxALIGN_RIGHT);

    //Bind buttons to functions
    Bind(wxEVT_BUTTON, &CameraSettingsDialog::OnOK, this, okButton->GetId());
    Bind(wxEVT_CLOSE_WINDOW, &CameraSettingsDialog::OnClose, this);

    // Set the main sizer
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(settingsSizer, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(autoSettingsSizer, 1, wxEXPAND | wxALL, 10);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);

    SetSizerAndFit(mainSizer);

    //controller->loadCurrentCameraSettings();
}

void CameraSettingsDialog::OnOK(wxCommandEvent& event)
{
	controller->onOK();
	this->Destroy();
}

void CameraSettingsDialog::OnClose(wxCloseEvent& event)
{
	controller->onClose();
	this->Destroy();
}
