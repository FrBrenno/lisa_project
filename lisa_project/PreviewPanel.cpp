#include "PreviewPanel.h"
#include "id/ButtonID.h"
#include <controller/CalibrationController.h>

PreviewPanel::PreviewPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(512, 512))
{
	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap placeholderBitmap("./img/lisa_logo.png", wxBITMAP_TYPE_PNG);
	this->imageControl = new wxStaticBitmap(this, wxID_ANY, placeholderBitmap, wxDefaultPosition, wxSize(512, 512));
	this->imageControl->SetDoubleBuffered(true);

	this->previewButton = new wxButton(this, ID_PREVIEW, "Start Preview");
	this->captureButton = new wxButton(this, ID_CAPTURE, "Capture");

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
	buttonSizer->Add(this->captureButton, 0, wxALIGN_CENTER | wxALL, 5);
	buttonSizer->Add(this->previewButton, 0, wxALIGN_CENTER | wxALL, 5);
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(this->imageControl, 0, wxALIGN_CENTER | wxALL, 5);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
	SetSizerAndFit(mainSizer);
}

PreviewPanel::~PreviewPanel()
{
	delete this->imageControl;
	delete this->previewButton;
	delete this->captureButton;
}

wxStaticBitmap* PreviewPanel::getPreviewImageControl()
{
	return this->imageControl;
}

wxButton* PreviewPanel::getPreviewButton()
{
	return this->previewButton;
}

wxButton* PreviewPanel::getCaptureButton()
{
	return this->captureButton;
}

void PreviewPanel::setPreviewListener(IPreviewHolderListener* listener)
{
	this->previewListener = listener;
}

void PreviewPanel::onCapture(wxWindow* parent)
{
	wxFileDialog saveFileDialog(parent, "Save Image", "", "", "PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxString filename = saveFileDialog.GetPath();
	wxImage image = this->imageControl->GetBitmap().ConvertToImage();
	image.SaveFile(filename, wxBITMAP_TYPE_PNG);
}

void PreviewPanel::loadImage()
{
	wxFileDialog openFileDialog(this, "Open Image", "", "", "PNG files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;
	wxString filename = openFileDialog.GetPath();
	wxImage image(filename, wxBITMAP_TYPE_PNG);

	// TEST PURPOSES
	// testing calibration pipeline
	CalibrationController calibrationController;
	cv::Mat img = cv::imread(filename.ToStdString());
	CalibrationData* calibrationData = calibrationController.applyCalibrationPipeline(img);
	cv::Mat calib_img = calibrationData->getImage();
	image = wxImage(calib_img.cols, calib_img.rows, calib_img.data, true);
	delete calibrationData;
	// END TEST PURPOSES

	this->setImage(&image);
}

void PreviewPanel::setImage(wxImage* image)
{
	this->imageControl->SetBitmap(wxNullBitmap);
	wxBitmap* bitmap = new wxBitmap(*image);
	imageControl->SetBitmap(*bitmap);
	imageControl->Refresh();
}
