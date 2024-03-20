#include "HomeFrameController.h"
#include "../view/InstrumentSelectionDialog.h"

HomeFrameController::HomeFrameController(MyAppInterface* main, IApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	if (!this->wfsApiService->isApiConnectionActive()) {
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
	/*CalibrationController calibrationController(this->app, this->wfsApiService);
	cv::Mat img = cv::imread(filePath.ToStdString());
	calibrationController.setImage(&img, img.rows, img.cols);
	calibrationController.calibrationPipeline();*/
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


