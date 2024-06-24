#pragma once
#include "CalibrationParametersDto.h"
#include "CalibrationData.h"
#include <string>

class ICalibrationViewListener {
public:
	virtual uint8_t validateParameters(CalibrationParametersDto param) = 0;
	virtual void OnDefaultParameters() = 0;
	virtual void SetCalibrationParameters(CalibrationParametersDto param) = 0;
	virtual CalibrationParametersDto GetCalibrationParameters() = 0;

	virtual CalibrationData OnCalibrate() = 0;
	virtual void OnShowErrorHeatmap() = 0;
	virtual std::vector<cv::Point2d> GetCircles() = 0;
	virtual void OnClose() = 0;

	virtual void SaveCalibrationData(std::string path) = 0;
	virtual CalibrationData GetCalibrationData() = 0;

	virtual void storeCalibrationDataPair() = 0;
	virtual void deleteCalibrationDataList() = 0;
	virtual CalibrationData computeGlobalResult() = 0;
	virtual void saveCalibrationDataListFile(std::string path) = 0;
};
