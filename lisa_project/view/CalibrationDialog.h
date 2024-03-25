#pragma once
#include <wx/wx.h>
#include "../interface/ICalibrationViewListener.h"
#include "PreviewPanel.h"
#include "../controller/PreviewController.h"

class CalibrationDialog : public wxDialog {
	wxWindow* parent;
	ICalibrationViewListener* listener;

	wxStaticBoxSizer* parametersBox;
	wxStaticBoxSizer* resultsBox;
	PreviewPanel* previewPanel;

	wxBoxSizer* mainSizer;
	wxBoxSizer* leftSizer;
public:
	CalibrationDialog(wxWindow* parent, ICalibrationViewListener* controller, IPreviewListener* previewListener);

	void ShowCalibrationDialog();
	PreviewPanel* getPreviewPanel();
};
