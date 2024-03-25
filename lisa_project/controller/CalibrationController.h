#pragma once
#include "BaseController.h"
#include "../interface/ICalibrationViewListener.h"
#include "../model/CalibrationData.h"
#include "PreviewController.h"

class CalibrationController: public BaseController, public ICalibrationViewListener{
	CalibrationData* calibrationData;
	PreviewController* previewController;

public:
	CalibrationController(MyAppInterface* main, IApiService* wfsApiService, ImageController* imageController);
	~CalibrationController();

	void HandleCalibrationStart();

	void OnClose() override;
};
