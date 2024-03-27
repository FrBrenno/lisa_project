#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "../interface/ICalibrationViewListener.h"
#include "PreviewPanel.h"
#include "../controller/PreviewController.h"
#include "../model/Dto/CalibrationParametersDto.h"

class CalibrationDialog : public wxDialog {
	wxWindow* parent;
	ICalibrationViewListener* listener;

	//=== Parameters ===//
	wxCheckBox* useInvertImage;
	wxSpinCtrl* gaussBlurSize;
	int m_gaussBlurSize;
	wxSpinCtrl* blockSize;
	int m_blockSize;
	wxSpinCtrl* c;
	wxSpinCtrl* clusterDistance;
	wxCheckBox* drawCircles;
	wxCheckBox* drawGrid;

	PreviewPanel* previewPanel;
	wxButton* calibrateButton;
	wxButton* saveButton;
	wxButton* loadButton;
	wxButton* defaultParametersButton;

	void updateParametersView(CalibrationParametersDto param);
	CalibrationParametersDto getCalibrationParameters();
	bool validateParameters(CalibrationParametersDto param);
public:
	CalibrationDialog(wxWindow* parent, ICalibrationViewListener* controller, IPreviewListener* previewListener);

	void ShowCalibrationDialog();
	PreviewPanel* getPreviewPanel();

	void OnOddSpin(wxSpinEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnCalibrate(wxCommandEvent& event);
	void OnDefaultParameters(wxCommandEvent& event);
};
