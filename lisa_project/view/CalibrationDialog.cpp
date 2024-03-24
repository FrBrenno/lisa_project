#include "CalibrationDialog.h"
#include "PreviewPanel.h"

CalibrationDialog::CalibrationDialog(wxWindow* parent, ICalibrationViewListener* listener) :
	wxDialog(parent, wxID_ANY, "LISA - PCV: Calibration")
{
	// Attributes setting
	this->parent = parent;
	this->listener = listener;

	//=== View Construction ===//
	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	parametersBox = new wxStaticBoxSizer(wxVERTICAL, this, "Parameters");
	resultsBox = new wxStaticBoxSizer(wxVERTICAL, this, "Results");	
	this->calibrationFrame = new wxStaticBitmap(this, wxID_ANY, wxBitmap(), wxDefaultPosition, wxSize(128, 128));

	// Left Sizer
	leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(parametersBox, 1, wxEXPAND | wxALL, 5);
	leftSizer->Add(resultsBox, 1, wxEXPAND | wxALL, 5);

	// Main Sizer
	mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 5);
	mainSizer->Add(calibrationFrame, 1, wxEXPAND | wxALL, 5);
		
	SetSizerAndFit(mainSizer);

	CenterOnScreen();

}

void CalibrationDialog::ShowCalibrationDialog()
{
	this->ShowModal();
}
