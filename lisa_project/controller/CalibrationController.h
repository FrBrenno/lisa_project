#pragma once
#include "BaseController.h"
#include "../interface/ICalibrationViewListener.h"
#include "../model/CalibrationData.h"

class CalibrationController: public BaseController, public ICalibrationViewListener{
	CalibrationData* calibrationData;

public:
	CalibrationController(MyAppInterface* main, IApiService* wfsApiService);
	~CalibrationController();

	void HandleCalibrationStart();
};
