#include "CalibrationController.h"
#include "../event/EventDispatcher.h"
#include "../event/CalibrationStartEvent.h"
#include "../view/CalibrationDialog.h"

CalibrationController::CalibrationController(MyAppInterface* main, IApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->calibrationData = new CalibrationData();

	EventDispatcher::Instance().SubscribeToEvent<CalibrationStartEvent>(
		[this](const CalibrationStartEvent& event) {
			HandleCalibrationStart();
		}
	);
}

CalibrationController::~CalibrationController()
{
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
	CalibrationDialog calibrationDialog(this->app->getHomeFrame(), this);
	calibrationDialog.ShowCalibrationDialog();
}

