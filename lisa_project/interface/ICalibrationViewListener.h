#pragma once
#include "../model/Dto/CalibrationParametersDto.h"

class ICalibrationViewListener {
public:
	virtual uint8_t validateParameters(CalibrationParametersDto param) = 0;
	virtual void OnDefaultParameters() = 0;
	virtual void SetCalibrationParameters(CalibrationParametersDto param) = 0;
	virtual CalibrationParametersDto GetCalibrationParameters() = 0;
	virtual void OnCalibrate() = 0;
	virtual void OnClose() = 0;
};
