#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "../interface/ICalibrationViewListener.h"
#include "PreviewPanel.h"
#include "../controller/PreviewController.h"

class CalibrationDialog : public wxDialog {
	wxWindow* parent;
	ICalibrationViewListener* listener;

	//=== Parameters ===//
	wxCheckBox* useInvertImage;
	wxSpinCtrl* gaussBlurSize;
	wxSpinCtrl* blockSize;
	wxSpinCtrl* c;
	wxSpinCtrl* clusterDistance;
	wxCheckBox* drawCircles;
	wxCheckBox* drawGrid;

	PreviewPanel* previewPanel;
	wxButton* calibrateButton;
	wxButton* saveButton;
	wxButton* loadButton;
	wxButton* defaultParametersButton;
public:
	CalibrationDialog(wxWindow* parent, ICalibrationViewListener* controller, IPreviewListener* previewListener);

	void ShowCalibrationDialog();
	PreviewPanel* getPreviewPanel();

	void OnClose(wxCloseEvent& event);
	void OnCalibrate(wxCommandEvent& event);	
};
