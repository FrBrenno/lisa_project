#include "HomeFrameController.h"
#include "../view/InstrumentSelectionDialog.h"
#include "ImageProcessingController.h"
#include "../EventDispatcher.h"

HomeFrameController::HomeFrameController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
}

wxImage HomeFrameController::onLoadImage(wxWindow* parent)
{
	wxFileDialog openFileDialog(parent, "Open Image", "", "", "PNG files (*.png)|*.png|All files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL) {
		// User canceled the operation
		return wxImage();
	}

	wxString filePath = openFileDialog.GetPath();

	// Ensure a valid file path
	if (filePath.empty()) {
		wxMessageBox("Invalid file path.", "Error", wxOK | wxICON_ERROR);
		return wxImage();
	}

	// Load the image
	wxImage image(filePath, wxBITMAP_TYPE_PNG);
	// TEST PURPOSES
	// testing calibration pipeline
	ImageProcessingController ipc = ImageProcessingController(this->app, this->wfsApiService);
	cv::Mat img = cv::imread(filePath.ToStdString());
	ipc.setImage(&img, img.rows, img.cols);
	ipc.calibrationPipeline();
	// END TEST PURPOSES

	if (!image.IsOk()) {
		wxMessageBox("Failed to load the image.", "Error", wxOK | wxICON_ERROR);
		// Return an empty wxBitmap or handle the error accordingly
		return wxImage();
	}

	return image;
}

void HomeFrameController::onConnectAPI()
{
	this->app->check_api_connection();
}


void HomeFrameController::onCapture(wxWindow* parent, wxBitmap lastBitmap)
{
	wxFileDialog saveFileDialog(parent, "Save Image", "", "pcv_image.png", "PNG files (*.png)|*.png|All files (*.*)|*.*", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		// User canceled the operation
		return;
	}

	wxString filePath = saveFileDialog.GetPath();

	// Ensure a valid file path
	if (filePath.empty()) {
		wxMessageBox("Invalid file path.", "Error", wxOK | wxICON_ERROR);
		return;
	}

	// Save the image
	lastBitmap.SaveFile(filePath, wxBITMAP_TYPE_PNG);
}


bool HomeFrameController::isWfsConnected()
{
	return this->wfsApiService->isApiConnectionActive();
}
