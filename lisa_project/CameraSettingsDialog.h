#pragma once
#include "wx/wx.h"
#include "CameraSettingsController.h"

class CameraSettingsDialog : public wxDialog
{
	wxWindow* parent;
	CameraSettingsController* listener;
public:
	CameraSettingsDialog(wxWindow* parent, CameraSettingsController* controller);
	void OnOK(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};
