#pragma once
#include "wx/wx.h"
#include "../controller/CameraSettingsController.h"

class CameraSettingsDialog : public wxDialog
{
	wxWindow* parent;
	CameraSettingsController* controller;
public:
	CameraSettingsDialog(wxWindow* parent, CameraSettingsController* controller);
	void OnOK(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
};
