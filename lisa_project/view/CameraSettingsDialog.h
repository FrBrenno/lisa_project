#pragma once
#include "wx/wx.h"
#include "../controller/CameraSettingsController.h"

class CameraSettingsDialog : public wxDialog
{
	wxWindow* parent;
	CameraSettingsController* controller;

	//=== View Elements ===//

	wxListBox* resolutionListBox;
	wxTextCtrl* nbImageReadingCtrl;
	wxTextCtrl* exposureTimeCtrl;
	wxTextCtrl* noiseCutLevelCtrl;
	wxTextCtrl* gainCtrl;
	wxTextCtrl* blackLevelCtrl;
	wxCheckBox* autoExposureButton;
	wxCheckBox* autoNoiseCutButton;
	wxCheckBox* autoBlackLevelButton;
	wxButton* setDefaultButton;
	wxButton* cancelButton;
	wxButton* okButton;

	wxString resolutionList[1] = { "512x512"};

	//=== Event Handlers ===//
	void OnTextCtrl(wxEvent& event);
	void OnAutoExposure(wxCommandEvent& event);
	void OnAutoNoiseCut(wxCommandEvent& event);
	void OnAutoBlackLevel(wxCommandEvent& event);
public:
	CameraSettingsDialog(wxWindow* parent, CameraSettingsController* controller);
	
	void loadCameraSettings(CameraConfig* cameraConfig);
	
	void OnSetDefault(wxCommandEvent& event);
	void OnOK(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};
