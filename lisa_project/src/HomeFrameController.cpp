#include "HomeFrameController.h"
#include "InstrumentSelectionDialog.h"
#include "CalibrationController.h"

HomeFrameController::HomeFrameController(MyAppInterface* main, IApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	if (!this->wfsApiService->isApiConnectionActive()) {
		// Call to main so it can try to connect to API
		this->handleError(-1, "WFS is not connected");
		return;
	}
}

void HomeFrameController::onConnectAPI()
{
	this->app->check_api_connection();
}


