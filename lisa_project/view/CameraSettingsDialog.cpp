#include "CameraSettingsDialog.h"
#include "../id/ButtonID.h"

CameraSettingsDialog::CameraSettingsDialog(wxWindow* parent, CameraSettingsController* controller)
	: wxDialog(parent, wxID_ANY, "Camera Settings")
{
	this->parent = parent;
	this->controller = controller;

	//=== View Construction ===//
    resolutionListBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxArrayString(), wxLB_SINGLE);
     nbImageReadingCtrl = new wxTextCtrl(this, wxID_ANY);
    exposureTimeCtrl = new wxTextCtrl(this, wxID_ANY);
    noiseCutLevelCtrl = new wxTextCtrl(this, wxID_ANY);
    gainCtrl = new wxTextCtrl(this, wxID_ANY, wxString::Format(wxT("%.2f"), 1.00));
    gainCtrl->Enable(false);
    blackLevelCtrl = new wxTextCtrl(this, wxID_ANY);
    
    autoExposureButton = new wxCheckBox(this, ID_AUTO_EXPOSURE, wxT("Auto"));
    Bind(wxEVT_CHECKBOX, &CameraSettingsDialog::OnAutoExposure, this, ID_AUTO_EXPOSURE);
    autoNoiseCutButton = new wxCheckBox(this, ID_AUTO_NOISE_CUT, wxT("Auto"));
    Bind(wxEVT_CHECKBOX, &CameraSettingsDialog::OnAutoNoiseCut, this, ID_AUTO_NOISE_CUT);
    autoBlackLevelButton = new wxCheckBox(this, ID_AUTO_BLACK_LEVEL, wxT("Auto"));
    Bind(wxEVT_CHECKBOX, &CameraSettingsDialog::OnAutoBlackLevel, this, ID_AUTO_BLACK_LEVEL);

   setDefaultButton = new wxButton(this, wxID_ANY, wxT("Set Default"));
   Bind(wxEVT_BUTTON, &CameraSettingsDialog::OnOK, this, setDefaultButton->GetId());
   cancelButton = new wxButton(this, wxID_ANY, wxT("Cancel"));
   Bind(wxEVT_BUTTON, &CameraSettingsDialog::OnOK, this, cancelButton->GetId());
   okButton = new wxButton(this, wxID_ANY, wxT("OK"));
   Bind(wxEVT_BUTTON, &CameraSettingsDialog::OnOK, this, okButton->GetId());

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
}

void CameraSettingsDialog::loadCameraSettings(CameraConfig* cameraConfig)
{
	// Load camera settings
    this->resolutionListBox->AppendString(resolutionList[0]);
    this->resolutionListBox->SetSelection(0);

    this->nbImageReadingCtrl->SetValue(wxString::Format(wxT("%d"), cameraConfig->getNbImageReadings()));
    this->exposureTimeCtrl->SetValue(wxString::Format(wxT("%.2f"), cameraConfig->getExposureTime()));
    this->noiseCutLevelCtrl->SetValue(wxString::Format(wxT("%d"), cameraConfig->getNoiseCutLevel()));
    this->gainCtrl->SetValue(wxString::Format(wxT("%.2f"), cameraConfig->getGain()));
    this->blackLevelCtrl->SetValue(wxString::Format(wxT("%d"), cameraConfig->getBlackLevel()));

    this->autoExposureButton->SetValue(true);
    this->autoNoiseCutButton->SetValue(true);
    this->autoBlackLevelButton->SetValue(true);

    exposureTimeCtrl->Enable(false);
    noiseCutLevelCtrl->Enable(false);
    blackLevelCtrl->Enable(false);
}

//=== Event Handlers ===//

void CameraSettingsDialog::OnAutoExposure(wxCommandEvent& event)
{
	if (autoExposureButton->GetValue())
		exposureTimeCtrl->Enable(false);
	else
		exposureTimeCtrl->Enable(true);
}

void CameraSettingsDialog::OnAutoNoiseCut(wxCommandEvent& event)
{
	if (autoNoiseCutButton->GetValue())
		noiseCutLevelCtrl->Enable(false);
	else
		noiseCutLevelCtrl->Enable(true);
}

void CameraSettingsDialog::OnAutoBlackLevel(wxCommandEvent& event)
{
	if (autoBlackLevelButton->GetValue())
		blackLevelCtrl->Enable(false);
	else
		blackLevelCtrl->Enable(true);
}

void CameraSettingsDialog::OnSetDefault(wxCommandEvent& event)
{
	controller->onSetDefault();
}

void CameraSettingsDialog::OnOK(wxCommandEvent& event)
{
    wxString res = resolutionListBox->GetStringSelection();
    int resInt = 0;
    // Convert the 512x512 string to int 512
    for (int i = 0; i < res.size(); i++) {
        if (res[i] != 'x') {
			resInt = resInt * 10 + (res[i] - '0');
		}
        else {
			break;
		}
	}

    CameraConfig* cameraConfig = new CameraConfig();
    cameraConfig->setCameraConfig(resInt,
        wxAtof(exposureTimeCtrl->GetValue()),
        wxAtof(gainCtrl->GetValue()),
        wxAtoi(noiseCutLevelCtrl->GetValue()),
        wxAtoi(blackLevelCtrl->GetValue()),
        wxAtoi(nbImageReadingCtrl->GetValue()),
        autoExposureButton->GetValue(),
        true, //autoGainButton->GetValue(), is set to true because WFS20 only has auto gain
        autoNoiseCutButton->GetValue(),
        autoBlackLevelButton->GetValue());

    this->controller->onOK(cameraConfig);
	this->Destroy();
}

void CameraSettingsDialog::OnClose(wxCloseEvent& event)
{
	controller->onClose();
	this->Destroy();
}
