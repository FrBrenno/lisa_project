#pragma once
#include "BaseController.h"
#include "../interface/ICalibrationViewListener.h"
#include "../model/CalibrationData.h"
#include "PreviewController.h"
#include "CalibrationEngine.h"

class CalibrationController: public BaseController, public ICalibrationViewListener{
	CalibrationData* calibrationData;
	PreviewController* previewController;
	CalibrationEngine* calibrationEngine;

public:
	CalibrationController(MyAppInterface* main, IApiService* wfsApiService, ImageController* imageController);
	~CalibrationController();

	void HandleCalibrationStart();

	void OnCalibrate() override;
	void OnClose() override;
};
