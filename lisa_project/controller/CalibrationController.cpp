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
	this->lastCalibrationFrame = nullptr;

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


void CalibrationController::SetCalibrationParameters(CalibrationParametersDto param)
{
	this->calibrationEngine->setParameters(param);
}

CalibrationParametersDto CalibrationController::GetCalibrationParameters()
{
	return this->calibrationEngine->getParameters();
}

void CalibrationController::OnClose()
{
	this->previewController->stopPreview();
	this->previewController->setPreview(nullptr);
}

void CalibrationController::OnCalibrate()
{
	if (this->previewController->getIsPreviewOn())
	{
		this->previewController->stopPreview();
		delete this->lastCalibrationFrame;
		this->lastCalibrationFrame = this->previewController->getFrame();
	}

	cv::Mat cvImage(lastCalibrationFrame->GetHeight(), lastCalibrationFrame->GetWidth(), CV_8UC3, lastCalibrationFrame->GetData());
	delete calibrationData;
	this->calibrationData = this->calibrationEngine->applyCalibrationPipeline(cvImage);
	wxImage procImage(calibrationData->getImage().cols, calibrationData->getImage().rows, calibrationData->getImage().data, true);
	this->previewController->setFrame(&procImage);
}

void CalibrationController::OnDefaultParameters()
{
	this->calibrationEngine->setDefaultParameters();
}
