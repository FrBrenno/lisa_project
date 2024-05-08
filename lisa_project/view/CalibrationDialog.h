#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "../interface/ICalibrationViewListener.h"
#include "PreviewPanel.h"
#include "../controller/PreviewController.h"
#include "../model/Dto/CalibrationParametersDto.h"
#include "../model/CalibrationData.h"

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

	//=== Results ===//
	wxStaticText* cx0_value;
	wxStaticText* cy0_value;
	wxStaticText* dx_value;
	wxStaticText* dy_value;
	wxStaticText* error_value;

	//=== Buttons ===//
	PreviewPanel* previewPanel;
	wxTextCtrl* apertureTextCtrl;
	wxButton* calibrateButton;
	wxButton* saveButton;
	wxButton* loadButton;
	wxButton* defaultParametersButton;

	//== Debug buttons ==//
	wxButton* showErrorHeatmap;
	wxButton* showCirclesPos;


	void updateParametersView(CalibrationParametersDto param);
	void updateResultsView(CalibrationData calibData);
	CalibrationParametersDto getCalibrationParameters();
	bool validateParameters(CalibrationParametersDto param);
	void OnApertureTextChanged(wxCommandEvent& textEvent);
public:
	CalibrationDialog(wxWindow* parent, ICalibrationViewListener* controller, IPreviewListener* previewListener);

	void ShowCalibrationDialog();
	PreviewPanel* getPreviewPanel();

	void OnOddSpin(wxSpinEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnCalibrate(wxCommandEvent& event);
	void OnDefaultParameters(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnLoad(wxCommandEvent& event);
	void OnShowErrorHeatmap(wxCommandEvent& event);
	void OnShowCirclesPos(wxCommandEvent& event);
};
