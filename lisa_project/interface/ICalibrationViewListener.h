#pragma once
#include "../model/Dto/CalibrationParametersDto.h"
#include "../model/CalibrationData.h"
#include <string>

class ICalibrationViewListener {
public:
	virtual uint8_t validateParameters(CalibrationParametersDto param) = 0;
	virtual void OnDefaultParameters() = 0;
	virtual void SetCalibrationParameters(CalibrationParametersDto param) = 0;
	virtual CalibrationParametersDto GetCalibrationParameters() = 0;

	virtual CalibrationData OnCalibrate() = 0;
	virtual void OnShowErrorHeatmap() = 0;
	virtual void OnClose() = 0;

	virtual void SaveCalibrationData(std::string path) = 0;
	virtual void LoadCalibrationData(std::string path) = 0;
	virtual CalibrationData GetCalibrationData() = 0;
};
