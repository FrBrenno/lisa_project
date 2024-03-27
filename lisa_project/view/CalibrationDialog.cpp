#include "CalibrationDialog.h"

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
	gaussBlurSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 15);
	m_gaussBlurSize = gaussBlurSize->GetValue();
	gaussBlurSize->Bind(wxEVT_SPINCTRL, &CalibrationDialog::OnOddSpin, this);
	gaussBlurSizeSizer->Add(gaussBlurSize, 0, wxALIGN_RIGHT | wxALL, 5);

	wxBoxSizer* blockSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* blockSizeLabel = new wxStaticText(this, wxID_ANY, "Block Size:");
	blockSizeSizer->Add(blockSizeLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	blockSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 5, 50, 31);
	m_blockSize = blockSize->GetValue();
	blockSize->Bind(wxEVT_SPINCTRL, &CalibrationDialog::OnOddSpin, this);
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
	defaultParametersButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnDefaultParameters, this);

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
	CalibrationParametersDto param = this->listener->GetCalibrationParameters();
	this->updateParametersView(param);
	this->ShowModal();
}

void CalibrationDialog::updateParametersView(CalibrationParametersDto param)
{
	this->useInvertImage->SetValue(param.getUseInvertImage());
	this->gaussBlurSize->SetValue(param.getGaussKernel().height);
	this->m_gaussBlurSize = param.getGaussKernel().height;
	this->blockSize->SetValue(param.getBlockSize());
	this->m_blockSize = param.getBlockSize();
	this->c->SetValue(param.getC());
	this->clusterDistance->SetValue(param.getClusterDistance());
	this->drawCircles->SetValue(param.getDrawCircles());
	this->drawGrid->SetValue(param.getDrawGrid());
}

CalibrationParametersDto CalibrationDialog::getCalibrationParameters()
{
	cv::Size gaussKernel(this->gaussBlurSize->GetValue(), this->gaussBlurSize->GetValue());
	int blockSize = this->blockSize->GetValue();
	double c = this->c->GetValue();
	double clusterDistance = this->clusterDistance->GetValue();
	bool useInvertImage = this->useInvertImage->GetValue();
	bool drawCircles = this->drawCircles->GetValue();
	bool drawGrid = this->drawGrid->GetValue();

	return CalibrationParametersDto(gaussKernel, blockSize, c, clusterDistance, useInvertImage, drawCircles, drawGrid);
}

bool CalibrationDialog::validateParameters(CalibrationParametersDto param)
{
	uint8_t error_code = this->listener->validateParameters(param);
	// Create a string and concatenate all the errors then show them in a message box
	wxString errors = "";
	// Check if the gauss kernel is odd
	if (error_code & 0x1)
	{
		errors += "Gauss Kernel must be an odd number\n";
	}

	// Check if the block size is odd
	if (error_code & 0x2)
	{
		errors += "Block Size must be an odd number\n";
	}

	// Check if the c value is positive
	if (error_code & 0x4)
	{
		errors += "C must be a positive number\n";
	}

	// Check if the cluster distance is positive
	if (error_code & 0x8)
	{
		errors += "Cluster Distance must be a positive number\n";
	}

	// If there are no errors return true
	if (errors.IsEmpty())
	{
		return true;
	}
	else
	{
		wxMessageBox(errors, "Invalid Parameters", wxICON_ERROR);
		return false;
	}
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
	CalibrationParametersDto param = this->getCalibrationParameters();
	if (this->validateParameters(param)) {
		this->listener->SetCalibrationParameters(param);
		this->listener->OnCalibrate();
	}
}

void CalibrationDialog::OnDefaultParameters(wxCommandEvent& event)
{
	this->listener->OnDefaultParameters();
	this->updateParametersView(this->listener->GetCalibrationParameters());
}

void CalibrationDialog::OnOddSpin(wxSpinEvent& event)
{
	wxSpinCtrl* spin = dynamic_cast<wxSpinCtrl*>(event.GetEventObject());
	if (spin){
		int currentValue;
		if (spin == gaussBlurSize) {
			currentValue = m_gaussBlurSize;
		}
		else if (spin == blockSize) {
			currentValue = m_blockSize;
		}
		else {
			currentValue = spin->GetValue();
		}
		int newValue = event.GetInt(); // Get the new value from the event

		// Determine the direction of spin
		bool isSpinningUp = (newValue > currentValue);

		if (newValue % 2 == 0){
			// Adjust the value based on spin direction
			if (isSpinningUp){
				newValue++;
			}
			else{
				newValue--;
			}
		}

		// Set the new value
		spin->SetValue(newValue);

		if (spin == gaussBlurSize) {
			m_gaussBlurSize = newValue;
		}
		else if (spin == blockSize) {
			m_blockSize = newValue;
		}
	}
	event.Skip(); // Allow default processing of the event
}

