#pragma once
#include "BaseController.h"
#include "ICalibrationViewListener.h"
#include "CalibrationData.h"
#include "CalibrationParametersDto.h"
#include "PreviewController.h"
#include "CalibrationEngine.h"
#include "nlohmann/json.hpp"


class CalibrationController: public BaseController, public ICalibrationViewListener{
	CalibrationData* calibrationData;
	PreviewController* previewController;
	CalibrationEngine* calibrationEngine;

	wxImage* lastCalibrationFrame;
	std::vector<std::pair<CalibrationParametersDto, CalibrationData>> calibrationDataList;

	wxImage drawOnImage(CalibrationData* calibData);
	void updateImage(cv::Mat image);
	nlohmann::ordered_json constructCalibrationJson(CalibrationParametersDto param, CalibrationData calibData, bool writeParam);
public:
	CalibrationController(MyAppInterface* main, IApiService* wfsApiService, ImageController* imageController);
	~CalibrationController();

	void HandleCalibrationStart();

	// ICalibrationViewListener
	uint8_t validateParameters(CalibrationParametersDto param) override;
	void OnDefaultParameters() override;
	void SetCalibrationParameters(CalibrationParametersDto param) override;
	CalibrationParametersDto GetCalibrationParameters() override;

	CalibrationData OnCalibrate() override;
	void OnShowErrorHeatmap() override;
	std::vector<cv::Point2d> GetCircles() override;
	void OnClose() override;

	void SaveCalibrationData(std::string path) override;
	CalibrationData GetCalibrationData() override;

	void storeCalibrationDataPair() override;
	void deleteCalibrationDataList() override;
	CalibrationData computeMeanResult() override;
	void saveCalibrationDataListFile(std::string path) override;
};
