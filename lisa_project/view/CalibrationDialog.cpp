#include "CalibrationDialog.h"
#include "PreviewPanel.h"

CalibrationDialog::CalibrationDialog(wxWindow* parent, ICalibrationViewListener* listener, IPreviewListener* previewListener) :
	wxDialog(parent, wxID_ANY, "LISA - PCV: Calibration")
{
	// Attributes setting
	this->parent = parent;
	this->listener = listener;

	//=== View Construction ===//
	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	parametersBox = new wxStaticBoxSizer(wxVERTICAL, this, "Parameters");
	resultsBox = new wxStaticBoxSizer(wxVERTICAL, this, "Results");	
	previewPanel = new PreviewPanel(this);
	previewPanel->setPreviewListener(previewListener);

	// Left Sizer
	leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(parametersBox, 1, wxEXPAND | wxALL, 5);
	leftSizer->Add(resultsBox, 1, wxEXPAND | wxALL, 5);

	// Main Sizer
	mainSizer->Add(leftSizer, 1, wxEXPAND | wxALL, 5);
	mainSizer->Add(previewPanel, 1, wxEXPAND | wxALL, 5);
		
	SetSizerAndFit(mainSizer);

	CenterOnScreen();

}

void CalibrationDialog::ShowCalibrationDialog()
{
	this->ShowModal();
}

PreviewPanel* CalibrationDialog::getPreviewPanel()
{
	return this->previewPanel;
}
