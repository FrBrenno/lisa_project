#include "CalibrationDialog.h"
#include <wx/grid.h>
#include <string>

CalibrationDialog::CalibrationDialog(wxWindow* parent, ICalibrationViewListener* listener, IPreviewListener* previewListener) :
	wxDialog(parent, wxID_ANY, "LISA - PCV: Calibration")
{
	// Attributes setting
	this->parent = parent;
	this->listener = listener;

	// Define font for labels and values
	wxFont font = this->GetFont();
	font.SetPointSize(12);

	//=== View Construction ===//

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	//=== Counter display
	wxBoxSizer* counterBox = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* counterLabel = new wxStaticText(this, wxID_ANY, "Calibration Counter:");
	counterLabel->SetFont(font);
	counterBox->Add(counterLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	calibCounter = new wxStaticText(this, wxID_ANY, "0");
	calibCounter->SetFont(font);
	counterBox->Add(calibCounter, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	wxStaticText* slashLabel = new wxStaticText(this, wxID_ANY, "/");
	slashLabel->SetFont(font);
	counterBox->Add(slashLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	wxStaticText* maxCalibLabel = new wxStaticText(this, wxID_ANY, "5");
	maxCalibLabel->SetFont(font);
	counterBox->Add(maxCalibLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	//=== Parameters
	wxStaticBoxSizer* parametersBox = new wxStaticBoxSizer(wxVERTICAL, this, "Parameters");

	useInvertImage = new wxCheckBox(this, wxID_ANY, "Invert Image");
	parametersBox->Add(useInvertImage, 0, wxALIGN_LEFT | wxALL, 5);
	drawCircles = new wxCheckBox(this, wxID_ANY, "Draw Circles");
	parametersBox->Add(drawCircles, 0, wxALIGN_LEFT | wxALL, 5);
	drawGrid = new wxCheckBox(this, wxID_ANY, "Draw Lines");
	parametersBox->Add(drawGrid, 0, wxALIGN_LEFT | wxALL, 5);

	wxBoxSizer* gaussBlurSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* gaussBlurSizeLabel = new wxStaticText(this, wxID_ANY, "Gauss Blur Size:");
	gaussBlurSizeSizer->Add(gaussBlurSizeLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	gaussBlurSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 51, 15);
	m_gaussBlurSize = gaussBlurSize->GetValue();
	gaussBlurSize->Bind(wxEVT_SPINCTRL, &CalibrationDialog::OnOddSpin, this);
	gaussBlurSizeSizer->Add(gaussBlurSize, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5); 

	wxBoxSizer* blockSizeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* blockSizeLabel = new wxStaticText(this, wxID_ANY, "Block Size:");
	blockSizeSizer->Add(blockSizeLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	blockSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 5, 51, 31);
	m_blockSize = blockSize->GetValue();
	blockSize->Bind(wxEVT_SPINCTRL, &CalibrationDialog::OnOddSpin, this);
	blockSizeSizer->Add(blockSize, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5); 

	wxBoxSizer* cSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* cLabel = new wxStaticText(this, wxID_ANY, "C:");
	cSizer->Add(cLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	c = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 1);
	cSizer->Add(c, 1, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxBoxSizer* clusterDistanceSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* clusterDistanceLabel = new wxStaticText(this, wxID_ANY, "Cluster Distance:");
	clusterDistanceSizer->Add(clusterDistanceLabel, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);
	clusterDistance = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 50, 1);
	clusterDistanceSizer->Add(clusterDistance, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5); 

	parametersBox->Add(gaussBlurSizeSizer, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 5); 
	parametersBox->Add(blockSizeSizer, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 5); 
	parametersBox->Add(cSizer, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 5); 
	parametersBox->Add(clusterDistanceSizer, 1, wxEXPAND | wxALIGN_CENTER_VERTICAL | wxALL, 5); 

	defaultParametersButton = new wxButton(this, wxID_ANY, "Default Parameters");
	defaultParametersButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnDefaultParameters, this);

	calibrateButton = new wxButton(this, wxID_ANY, "Calibrate");
	calibrateButton->SetFont(font);
	calibrateButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnCalibrate, this);
	calibrateButton->SetToolTip("Please set the aperture before submitting");


	//=== Results
	wxStaticBoxSizer* resultsBox = new wxStaticBoxSizer(wxVERTICAL, this, "Results");

	wxBoxSizer* cx0Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* cx0Label = new wxStaticText(this, wxID_ANY, "Cx0:");
	cx0Label->SetFont(font); // Set font for the label
	cx0Sizer->Add(cx0Label, 1, wxALIGN_RIGHT | wxALL, 5);
	cx0_value = new wxStaticText(this, wxID_ANY, "0");
	cx0_value->SetFont(font); // Set font for the value
	cx0Sizer->Add(cx0_value, 1, wxALIGN_LEFT | wxALL, 5);

	wxBoxSizer* cy0Sizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* cy0Label = new wxStaticText(this, wxID_ANY, "Cy0:");
	cy0Label->SetFont(font); // Set font for the label
	cy0Sizer->Add(cy0Label, 1, wxALIGN_RIGHT | wxALL, 5);
	cy0_value = new wxStaticText(this, wxID_ANY, "0");
	cy0_value->SetFont(font); // Set font for the value
	cy0Sizer->Add(cy0_value, 1, wxALIGN_LEFT | wxALL, 5);

	wxBoxSizer* dxSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* dxLabel = new wxStaticText(this, wxID_ANY, "dx:");
	dxLabel->SetFont(font); // Set font for the label
	dxSizer->Add(dxLabel, 1, wxALIGN_RIGHT | wxALL, 5);
	dx_value = new wxStaticText(this, wxID_ANY, "0");
	dx_value->SetFont(font); // Set font for the value
	dxSizer->Add(dx_value, 1, wxALIGN_LEFT | wxALL, 5);

	wxBoxSizer* dySizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* dyLabel = new wxStaticText(this, wxID_ANY, "dy:");
	dyLabel->SetFont(font); // Set font for the label
	dySizer->Add(dyLabel, 1, wxALIGN_RIGHT | wxALL, 5);
	dy_value = new wxStaticText(this, wxID_ANY, "0");
	dy_value->SetFont(font); // Set font for the value
	dySizer->Add(dy_value, 1, wxALIGN_LEFT | wxALL, 5);

	wxBoxSizer* errorSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* errorLabel = new wxStaticText(this, wxID_ANY, "Error:");
	errorLabel->SetFont(font); // Set font for the label
	errorSizer->Add(errorLabel, 1, wxALIGN_RIGHT | wxALL, 5);
	error_value = new wxStaticText(this, wxID_ANY, "0");
	error_value->SetFont(font); // Set font for the value
	errorSizer->Add(error_value, 1, wxALIGN_LEFT | wxALL, 5);

	showErrorHeatmap = new wxButton(this, wxID_ANY, "Show Error Heatmap");
	showErrorHeatmap->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	showErrorHeatmap->Bind(wxEVT_BUTTON, &CalibrationDialog::OnShowErrorHeatmap, this);

	showCirclesPos = new wxButton(this, wxID_ANY, "Show Circles Position");
	showCirclesPos->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	showCirclesPos->Bind(wxEVT_BUTTON, &CalibrationDialog::OnShowCirclesPos, this);

	// Add sizers for each parameter to the resultsBox
	wxBoxSizer* resultsRefCircle = new wxBoxSizer(wxVERTICAL);
	resultsRefCircle->Add(cx0Sizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5);
	resultsRefCircle->Add(cy0Sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	wxBoxSizer* resultsGridSpacing = new wxBoxSizer(wxVERTICAL);
	resultsGridSpacing->Add(dxSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	resultsGridSpacing->Add(dySizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	wxBoxSizer* resultsError = new wxBoxSizer(wxVERTICAL);
	resultsError->Add(errorSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	wxBoxSizer* resultsSubBox = new wxBoxSizer(wxHORIZONTAL);
	resultsSubBox->Add(resultsRefCircle, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	resultsSubBox->Add(resultsGridSpacing, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	resultsSubBox->Add(resultsError, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
	resultsBox->Add(resultsSubBox, 0, wxEXPAND | wxALL, 5);
	resultsBox->Add(showErrorHeatmap, 0, wxEXPAND | wxALL, 5);
	resultsBox->Add(showCirclesPos, 0, wxEXPAND | wxALL, 5);	

	// Buttons Confirm and Restart calibration process
	wxBoxSizer* confirmRestartButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	restartButton = new wxButton(this, wxID_ANY, "Restart");
	restartButton->SetFont(font);
	restartButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnRestart, this);
	confirmRestartButtonsSizer->Add(restartButton, 1, wxEXPAND | wxALL, 5);
	confirmButton = new wxButton(this, wxID_ANY, "Confirm");
	confirmButton->SetFont(font);
	confirmButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnConfirm, this);
	confirmRestartButtonsSizer->Add(confirmButton, 1, wxEXPAND | wxALL, 5);

	previewPanel = new PreviewPanel(this);
	previewPanel->setPreviewListener(previewListener);

	wxBoxSizer* apertureTextCtrlSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* apertureTextCtrlLabel = new wxStaticText(this, wxID_ANY, "Aperture:");
	apertureTextCtrlLabel->SetFont(font); // Set font for the label
	apertureTextCtrlSizer->Add(apertureTextCtrlLabel, 0, wxALIGN_LEFT | wxALL, 2);
	apertureTextCtrl = new wxTextCtrl(this, wxID_ANY, "");
	apertureTextCtrl->SetFocus();
	apertureTextCtrl->SetFont(font); // Set font for the value
	apertureTextCtrlSizer->Add(apertureTextCtrl, 1, wxALIGN_LEFT | wxALL, 2);

	wxStaticBoxSizer* fileBox = new wxStaticBoxSizer(wxVERTICAL, this, "File");
	saveButton = new wxButton(this, wxID_ANY, "Save Calibration File");
	saveButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	saveButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnSave, this);
	fileBox->Add(saveButton, 0, wxEXPAND | wxALL, 5);
	loadButton = new wxButton(this, wxID_ANY, "Load Calibration File");
	loadButton->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
 	loadButton->Bind(wxEVT_BUTTON, &CalibrationDialog::OnLoad, this);
	fileBox->Add(loadButton, 0, wxEXPAND | wxALL, 5);

	Bind(wxEVT_CLOSE_WINDOW, &CalibrationDialog::OnClose, this);

	// Left Sizer
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	leftSizer->Add(fileBox, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(counterBox, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(parametersBox, 1, wxEXPAND | wxALL, 5);
	wxBoxSizer* leftButtonsSizer = new wxBoxSizer(wxHORIZONTAL);
	leftButtonsSizer->Add(defaultParametersButton, 1, wxEXPAND | wxALL, 5);
	leftButtonsSizer->Add(calibrateButton, 1, wxEXPAND | wxALL, 5);
	leftSizer->Add(leftButtonsSizer, 0, wxEXPAND | wxALL, 5);
	leftSizer->Add(resultsBox, 0, wxEXPAND | wxALL, 5);

	// RightSizer
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
	rightSizer->Add(apertureTextCtrlSizer, 0, wxEXPAND | wxALL, 5);
	rightSizer->Add(previewPanel, 0, wxEXPAND | wxALL, 5);
	rightSizer->Add(confirmRestartButtonsSizer, 0, wxEXPAND | wxALL, 5);

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
	this->apertureTextCtrl->SetValue(param.getAperture());
}

void CalibrationDialog::updateResultsView(CalibrationData calibData)
{
	this->cx0_value->SetLabel(wxString::Format("%.2f", calibData.getRefCircle().x));
	this->cy0_value->SetLabel(wxString::Format("%.2f", calibData.getRefCircle().y));
	this->dx_value->SetLabel(wxString::Format("%.4f mm", calibData.getGridSpacing()[0]));
	this->dy_value->SetLabel(wxString::Format("%.4f mm", calibData.getGridSpacing()[1]));
	this->error_value->SetLabel(wxString::Format("%.4f mm", calibData.getError()));
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
	std::string aperture = this->apertureTextCtrl->GetValue().ToStdString();

	return CalibrationParametersDto(gaussKernel, blockSize, c, clusterDistance, useInvertImage, drawCircles, drawGrid, aperture);
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

	// Check if the aperture name is valid
	if (error_code & 0x10)
	{
		errors += "Aperture name is invalid\n";
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
	// Verify if aperture is set
	if (this->apertureTextCtrl->GetValue().IsEmpty())
	{
		wxMessageBox("Please set the aperture name before calibrating", "Aperture not set", wxICON_ERROR);
		apertureTextCtrl->SetFocus();
		return;
	}

	// Get the calibration parameters
	CalibrationParametersDto param = this->getCalibrationParameters();

	if (this->validateParameters(param)) {
		this->listener->SetCalibrationParameters(param);
		CalibrationData calibData = this->listener->OnCalibrate();
		this->updateResultsView(calibData);
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

void CalibrationDialog::OnSave(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save Calibration File"), "", "", "Calibration Files (*.calib)|*.calib|*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// Save the file
	this->listener->SaveCalibrationData(saveFileDialog.GetPath().ToStdString());
}

void CalibrationDialog::OnLoad(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open Calibration File"), "", "", "Calibration Files (*.calib)|*.calib|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// Load the file
	this->listener->LoadCalibrationData(openFileDialog.GetPath().ToStdString());
	this->updateResultsView(this->listener->GetCalibrationData());
	this->updateParametersView(this->listener->GetCalibrationParameters());
}

void CalibrationDialog::OnShowErrorHeatmap(wxCommandEvent& event)
{
	this->listener->OnShowErrorHeatmap();
}

void CalibrationDialog::OnShowCirclesPos(wxCommandEvent& event)
{
	std::vector<cv::Point2d> circles = this->listener->GetCircles();

	// Create a frame to contain the grid
	wxFrame* frame = new wxFrame(this, wxID_ANY, "Circles Position", wxDefaultPosition, wxSize(400, 300));

	// Create a grid to display circle positions
	wxGrid* grid = new wxGrid(frame, wxID_ANY);
	grid->CreateGrid(circles.size(), 2);

	// Set column labels
	grid->SetColLabelValue(0, "X");
	grid->SetColLabelValue(1, "Y");

	// Set row labels (optional)
	for (int i = 0; i < circles.size(); ++i) {
		grid->SetRowLabelValue(i, wxString::Format("Circle %d", i + 1));
	}

	// Set cell values
	for (int i = 0; i < circles.size(); ++i) {
		grid->SetCellValue(i, 0, wxString::Format("%.2f", circles[i].x));
		grid->SetCellValue(i, 1, wxString::Format("%.2f", circles[i].y));
	}

	// Show the frame
	frame->Show();
}

void CalibrationDialog::resetUI()
{
	// set default parameters
	this->listener->OnDefaultParameters();
	this->updateParametersView(this->listener->GetCalibrationParameters());
	// clear results
	this->updateResultsView(CalibrationData());
}

void CalibrationDialog::OnConfirm(wxCommandEvent& event)
{
	// Stores pair CalibrationParameterDto and CalibrationData in a vector
	this->listener->storeCalibrationDataPair();
	// Update the counter
	int counter = std::stoi(calibCounter->GetLabel().ToStdString());
	counter++;
	calibCounter->SetLabel(std::to_string(counter));

	if (counter < 4)
	{
		this->resetUI();
	}
	else if (counter == 5) {
		// If the counter is 5, disable the calibrate button and reset the UI
		calibrateButton->Disable();
		this->resetUI();
		// Compute the general result and show it
		CalibrationData meanResult = this->listener->computeMeanResult();
		this->updateResultsView(meanResult);

		// change button label to finish
		confirmButton->SetLabel("Finish");
		return;
	} else{
		// if the counter is 6, save the calibration data and close the dialog
		// this->listener->saveCalibrationDataList();
		// this->EndModal(wxOK);
		return;
	}
}

void CalibrationDialog::OnRestart(wxCommandEvent& event)
{
	// Delete all the stored calibration data
	this->listener->deleteCalibrationDataList();
	// Reset the counter
	calibCounter->SetLabel("0");
	// Enable the calibrate button
	calibrateButton->Enable();
	// Reset calibration ui for the next calibration
	this->resetUI();
}
