#include "CalibrationController.h"
#include "../event/EventDispatcher.h"
#include "../event/CalibrationStartEvent.h"
#include "../view/CalibrationDialog.h"

CalibrationController::CalibrationController(MyAppInterface* main, IApiService* wfsApiService, ImageController* imageController) :
	BaseController(main, wfsApiService)
{
	this->previewController = new PreviewController(main, wfsApiService, imageController);
	this->calibrationData = new CalibrationData();
	this->calibrationEngine = new CalibrationEngine();

	EventDispatcher::Instance().SubscribeToEvent<CalibrationStartEvent>(
		[this](const CalibrationStartEvent& event) {
			HandleCalibrationStart();
		}
	);
}

CalibrationController::~CalibrationController()
{
	delete previewController;
	delete calibrationData;
}

void CalibrationController::HandleCalibrationStart()
{
	if (!this->wfsApiService->isApiConnectionActive()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// Launch CalibrationDialog view
	CalibrationDialog calibrationDialog(this->app->getHomeFrame(), this, this->previewController);
	this->previewController->setPreview(calibrationDialog.getPreviewPanel());
	calibrationDialog.ShowCalibrationDialog();
}

void CalibrationController::OnClose()
{
	this->previewController->stopPreview();
	this->previewController->setPreview(nullptr);
}

void CalibrationController::OnCalibrate()
{
	this->previewController->stopPreview();
	wxImage* image = this->previewController->getFrame();
	if (image == nullptr)
	{
		this->handleError(-1, "No image to calibrate");
		return;
	}
	cv::Mat cvImage(image->GetHeight(), image->GetWidth(), CV_8UC3, image->GetData());
	delete calibrationData;
	this->calibrationData = this->calibrationEngine->applyCalibrationPipeline(cvImage);
	wxImage procImage(calibrationData->getImage().cols, calibrationData->getImage().rows, calibrationData->getImage().data, true);
	this->previewController->setFrame(&procImage);
	delete image;
}
