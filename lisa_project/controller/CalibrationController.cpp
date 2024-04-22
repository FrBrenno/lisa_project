#include "CalibrationController.h"
#include "../event/EventDispatcher.h"
#include "../event/CalibrationStartEvent.h"
#include "../view/CalibrationDialog.h"
#include "../lib/nlohmann/json.hpp"
#include <fstream>

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
	this->previewController->startPreview();
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

CalibrationData CalibrationController::OnCalibrate()
{
	// Collect the last frame for calibration if it has changed
	if (this->previewController->getIsPreviewOn()) {
		this->previewController->stopPreview();
	}

	if (this->previewController->getHasImageChanged()) {
		if (this->lastCalibrationFrame != nullptr) {
			delete this->lastCalibrationFrame;
		}
		this->lastCalibrationFrame = this->previewController->getFrame();
	}

	// Convert the frame to a cv::Mat
	cv::Mat cvImage(lastCalibrationFrame->GetHeight(), lastCalibrationFrame->GetWidth(), CV_8UC3, lastCalibrationFrame->GetData());
	
	// Delete the previous calibration data & apply the calibration pipeline
	if (this->calibrationData != nullptr)
	{
		delete this->calibrationData;
	}

	// Apply calibration pipeline and display the processed image
	CalibrationData* results = this->calibrationEngine->applyCalibrationPipeline(cvImage);
	if (results == nullptr)
	{
		return CalibrationData();
	}
	this->calibrationData = results;

	// Display the processed image
	wxImage procImage(results->getImage().cols, results->getImage().rows, results->getImage().data, true);
	this->previewController->setFrame(&procImage, false);
	return *results;
}

void CalibrationController::OnDefaultParameters()
{
	this->calibrationEngine->setDefaultParameters();
}

uint8_t CalibrationController::validateParameters(CalibrationParametersDto param)
{
	uint8_t errors = 0x0;
	// Check if the gauss kernel is odd
	if (param.getGaussKernel().height % 2 == 0 || param.getGaussKernel().width % 2 == 0)
	{
		errors |= 0x1; // 0001
	}

	// Check if the block size is odd
	if (param.getBlockSize() % 2 == 0)
	{
		errors |= 0x2; // 0010
	}

	// Check if the c value is positive
	if (param.getC() <= 0)
	{
		errors |= 0x4; // 0100
	}

	// Check if the cluster distance is positive
	if (param.getClusterDistance() <= 0)
	{
		errors |= 0x8; // 1000
	}
	return errors;
}

void CalibrationController::SaveCalibrationData(std::string path)
{
	// Gather all information to save: calibration parameters, calibration data
	CalibrationParametersDto param = this->calibrationEngine->getParameters();

	// Save image next to the calibration data
	std::string imagePath = path + ".png";
	cv::Mat cvImage(this->calibrationData->getImage().cols, this->calibrationData->getImage().rows, CV_8UC3, this->calibrationData->getImage().data);
	cv::imwrite(imagePath, cvImage);

	// Save to file in a JSON format
	nlohmann::json j;
	j["gaussKernel"] = { param.getGaussKernel().width, param.getGaussKernel().height };
	j["blockSize"] = param.getBlockSize();
	j["c"] = param.getC();
	j["clusterDistance"] = param.getClusterDistance();
	j["useInvertImage"] = param.getUseInvertImage();
	j["drawCircles"] = param.getDrawCircles();
	j["drawGrid"] = param.getDrawGrid();

	j["image"] = imagePath;
	j["cx0"] = this->calibrationData->getRefCircle().x;
	j["cy0"] = this->calibrationData->getRefCircle().y;
	j["dx"] = this->calibrationData->getGridSpacing()[0];
	j["dy"] = this->calibrationData->getGridSpacing()[1];

	j["circles"] = nlohmann::json::array();
	for (auto& circle : this->calibrationData->getCircles())
	{
		j["circles"].push_back({ circle.x, circle.y });
	}

	// Save to file
	std::ofstream file(path);
	file << j.dump(4);
	file.close();

}

void CalibrationController::LoadCalibrationData(std::string path)
{
	// Load from file
	std::ifstream file(path);
	nlohmann::json j;
	file >> j;
	file.close();

	// Load image
	std::string imagePath = j["image"];
	cv::Mat cvImage = cv::imread(imagePath);
	wxImage image(cvImage.cols, cvImage.rows, cvImage.data, true);
	this->previewController->setFrame(&image);

	// Load calibration parameters
	CalibrationParametersDto param(
		cv::Size(j["gaussKernel"][0], j["gaussKernel"][1]),
		j["blockSize"],
		j["c"],
		j["clusterDistance"],
		j["useInvertImage"],
		j["drawCircles"],
		j["drawGrid"]
	);
	this->calibrationEngine->setParameters(param);

	// Load calibration data
	std::vector<cv::Point2d> circles;
	for (auto& circle : j["circles"])
	{
		circles.push_back(cv::Point2d(circle[0], circle[1]));
	}
	CalibrationData* calibData = new CalibrationData(cvImage, (double)j["cx0"], (double)j["cy0"], (double)j["dx"], (double)j["dy"], circles);
	delete this->calibrationData;
	this->calibrationData = calibData;
}

CalibrationData CalibrationController::GetCalibrationData()
{
	return *this->calibrationData;
}
