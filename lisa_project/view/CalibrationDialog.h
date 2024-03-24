#pragma once
#include <wx/wx.h>
#include "../interface/ICalibrationViewListener.h"

class CalibrationDialog : public wxDialog {
	wxWindow* parent;
	ICalibrationViewListener* listener;

	wxStaticBoxSizer* parametersBox;
	wxStaticBoxSizer* resultsBox;
	wxStaticBitmap* calibrationFrame;

	wxBoxSizer* mainSizer;
	wxBoxSizer* leftSizer;
public:
	CalibrationDialog(wxWindow* parent, ICalibrationViewListener* controller);

	void ShowCalibrationDialog();
};
