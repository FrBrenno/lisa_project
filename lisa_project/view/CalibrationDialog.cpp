#include "CalibrationDialog.h"
#include "PreviewPanel.h"

CalibrationDialog::CalibrationDialog(wxWindow* parent, ICalibrationViewListener* listener, IPreviewListener* previewListener) :
	wxDialog(parent, wxID_ANY, "LISA - PCV: Calibration")
{
	// Attributes setting
	this->parent = parent;
	this->listener = listener;

	//=== View Construction ===//
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticBoxSizer* parametersBox = new wxStaticBoxSizer(wxVERTICAL, this, "Parameters");

	useInvertImage = new wxCheckBox(this, wxID_ANY, "Invert Image");
	drawCircles = new wxCheckBox(this, wxID_ANY, "Draw Circles");
	drawGrid = new wxCheckBox(this, wxID_ANY, "Draw Lines");

	wxBoxSizer* gaussBlurSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gaussBlurSizeLabel = new wxStaticText(this, wxID_ANY, "Gauss Blur Size:");
	gaussBlurSizeSizer->Add(gaussBlurSizeLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	gaussBlurSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 2);
	gaussBlurSizeSizer->Add(gaussBlurSize, 0, wxALIGN_RIGHT | wxALL, 5);

	wxBoxSizer* blockSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* blockSizeLabel = new wxStaticText(this, wxID_ANY, "Block Size:");
	blockSizeSizer->Add(blockSizeLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	blockSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 1);
	blockSizeSizer->Add(blockSize, 0, wxALIGN_RIGHT | wxALL, 5);

	wxBoxSizer* cSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* cLabel = new wxStaticText(this, wxID_ANY, "C:");
	cSizer->Add(cLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	c = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 1);
	cSizer->Add(c, 0, wxALIGN_RIGHT | wxALL, 5);

	wxBoxSizer* clusterDistanceSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* clusterDistanceLabel = new wxStaticText(this, wxID_ANY, "Cluster Distance:");
	clusterDistanceSizer->Add(clusterDistanceLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	clusterDistance = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 1);
	clusterDistanceSizer->Add(clusterDistance, 0, wxALIGN_RIGHT | wxALL, 5);

	parametersBox->Add(useInvertImage, 0, wxALIGN_LEFT| wxALL, 5);
	parametersBox->Add(drawCircles, 0, wxALIGN_LEFT | wxALL, 5);
	parametersBox->Add(drawGrid, 0, wxALIGN_LEFT | wxALL, 5);

	parametersBox->Add(gaussBlurSizeSizer, 0, wxALIGN_LEFT | wxALL, 5);
	parametersBox->Add(blockSizeSizer, 0, wxALIGN_LEFT | wxALL, 5);
	parametersBox->Add(cSizer, 0, wxALIGN_LEFT | wxALL, 5);
	parametersBox->Add(clusterDistanceSizer, 0, wxALIGN_LEFT | wxALL, 5);


	defaultParametersButton = new wxButton(this, wxID_ANY, "Default Parameters");
	// TODO: Bind defaultParametersButton to a method

	wxStaticBoxSizer* resultsBox = new wxStaticBoxSizer(wxVERTICAL, this, "Results");

	previewPanel = new PreviewPanel(this);
	previewPanel->setPreviewListener(previewListener);

	calibrateButton = new wxButton(this, wxID_ANY, "Calibrate");
	calibrateButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	calibrateButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnCalibrate, this);

	saveButton = new wxButton(this, wxID_ANY, "Save");
	saveButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	// TODO: Bind saveButton to a method
	loadButton = new wxButton(this, wxID_ANY, "Load");
	loadButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	// TODO: Bind loadButton to a method

	Bind(wxEVT_CLOSE_WINDOW, &CalibrationDialog::OnClose, this);

	// Left Sizer
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(parametersBox, 1, wxEXPAND | wxALL, 5);
	leftSizer->Add(defaultParametersButton, 0, wxALIGN_CENTER | wxALL, 5);
	leftSizer->Add(resultsBox, 1, wxEXPAND | wxALL, 5);

	// RightSizer
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
	rightSizer->Add(previewPanel, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonsSizer->Add(saveButton, 1, wxEXPAND | wxALL, 5);
	buttonsSizer->Add(loadButton, 1, wxEXPAND | wxALL, 5);
	buttonsSizer->Add(calibrateButton, 1, wxEXPAND | wxALL, 5);

	rightSizer->Add(buttonsSizer, 0, wxEXPAND | wxALL, 5);

	// Main Sizer
	mainSizer->Add(leftSizer, 0, wxEXPAND | wxALL, 5);
	mainSizer->Add(rightSizer, 1, wxEXPAND | wxALL, 5);
		
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

void CalibrationDialog::OnClose(wxCloseEvent& event)
{
	this->listener->OnClose();
	this->EndModal(wxOK);
}

void CalibrationDialog::OnCalibrate(wxCommandEvent& event)
{
	this->listener->OnCalibrate();
}
