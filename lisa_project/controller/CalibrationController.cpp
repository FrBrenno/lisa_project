#include "CalibrationController.h"
#include "../event/EventDispatcher.h"
#include "../event/CalibrationStartEvent.h"
#include "../view/CalibrationDialog.h"
#include "../lib/nlohmann/json.hpp"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <regex>

CalibrationController::CalibrationController(MyAppInterface* main, IApiService* wfsApiService, ImageController* imageController) :
	BaseController(main, wfsApiService)
{
	this->previewController = new PreviewController(main, wfsApiService, imageController);
	this->calibrationData = new CalibrationData();
	this->calibrationEngine = new CalibrationEngine();
	this->lastCalibrationFrame = nullptr;
	this->calibrationDataList = std::vector<std::pair<CalibrationParametersDto, CalibrationData>>();

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
	delete calibrationEngine;
	if (this->lastCalibrationFrame != nullptr) {
		delete this->lastCalibrationFrame;
	}
	// TODO: delete all calibration data in the list
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

wxImage CalibrationController::drawOnImage(CalibrationData* calibData) {
	CalibrationParametersDto param = this->calibrationEngine->getParameters();
	std::vector<cv::Point2d> circles = calibData->getCircles();
	std::vector<double> gridSpacing = calibData->getGridSpacing();
	cv::Mat cvImage = calibData->getImage();
	cv::Point2d refCircle = calibData->getRefCircle();

	// draw circle centers
	for (const auto& c : circles) {
		cv::circle(cvImage, c, 1, cv::Scalar(255, 255, 0), -1);
	}

	if (param.getDrawCircles()){
		double radius = (gridSpacing[0] + gridSpacing[1]) / 4;
		for (const auto& c : circles) {
			cv::circle(cvImage, c, radius, cv::Scalar(255, 255, 0), 1);
		}
	}

	if (param.getDrawGrid()) {
		// Vertical lines: x = cx0 + i*dx
		double startX = refCircle.x - gridSpacing[0]/2;
		for (double x = startX; x < cvImage.cols; x += gridSpacing[0]) {
			// draw grid line
			cv::line(cvImage, cv::Point(x, 0), cv::Point(x, cvImage.rows), cv::Scalar(0, 0, 255), 1);
		}
		// Horizontal lines: y = cy0 + i*dy
		double startY = refCircle.y - gridSpacing[1]/2;
		for (double y = startY; y < cvImage.rows; y += gridSpacing[1]) {
			cv::line(cvImage, cv::Point(0, y), cv::Point(cvImage.cols, y), cv::Scalar(0, 0, 255), 1);
		}

	}

	rectangle(cvImage, cv::Point(0, 0), cv::Point(215, 30), cv::Scalar(0, 0, 0), -1);
	putText(cvImage, "Calibration Result Frame", cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

	return wxImage(cvImage.cols, cvImage.rows, cvImage.data, true);
}


void CalibrationController::updateImage(cv::Mat image) {
	// TODO: add flag to do draw or not
	wxImage wxImage = this->drawOnImage(this->calibrationData);
	this->previewController->setFrame(&wxImage, false);
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
		this->lastCalibrationFrame = new wxImage(this->previewController->getFrame());
	}

	// Convert the frame to a cv::Mat
	cv::Mat cvImage(lastCalibrationFrame->GetHeight(), lastCalibrationFrame->GetWidth(), CV_8UC3, lastCalibrationFrame->GetData());


	// Apply calibration pipeline and display the processed image
	CalibrationData* results = this->calibrationEngine->applyCalibrationPipeline(cvImage);
	if (results == nullptr)
	{
		this->handleError(-1, "Calibration failed !\n\nThis frame is not adequate for calibration.");
		return CalibrationData();
	}
	// Delete the previous calibration data & set the new one
	if (this->calibrationData != nullptr)
	{
		delete this->calibrationData;
		this->calibrationData = results;
	}
	
	this->updateImage(cvImage);
	return *results;
}

void CalibrationController::OnShowErrorHeatmap()
{
	if (this->calibrationData == nullptr)
	{
		this->handleError(-1, "No calibration data available");
		return;
	}

	if (this->calibrationData->getErrorHeatmap().empty())
	{
		this->handleError(-1, "No error heatmap available");
		return;
	}

	cv::Mat errorHeatmap = this->calibrationData->getErrorHeatmap();
	cv::imshow("Error Heatmap", errorHeatmap);
}

std::vector<cv::Point2d> CalibrationController::GetCircles()
{
	if (this->calibrationData == nullptr)
	{
		this->handleError(-1, "No calibration data available");
		return std::vector<cv::Point2d>();
	}

	std::vector<cv::Point2d> circles = this->calibrationData->getCircles();
	if (circles.empty())
	{
		this->handleError(-1, "No circles available");
		return std::vector<cv::Point2d>();
	}

	return circles;
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

	// Check if aperture name is valid: only alphanumeric characters and underscore
	std::string apertureName = param.getAperture();
	if (!std::regex_match(apertureName, std::regex("^[a-zA-Z0-9_]*$")))
	{
		errors |= 0x10; // 0001 0000
	}
	
	return errors;
}

void CalibrationController::SaveCalibrationData(std::string path)
{
	// Gather all information to save: calibration parameters, calibration data
	CalibrationParametersDto param = this->calibrationEngine->getParameters();

	// Save image next to the calibration data
	std::string imagePath = path + ".png";
	cv::Mat cvImage(this->lastCalibrationFrame->GetHeight(), this->lastCalibrationFrame->GetWidth(), CV_8UC3, this->lastCalibrationFrame->GetData());
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
	j["aperture"] = param.getAperture();

	j["image"] = imagePath;
	j["cx0"] = this->calibrationData->getRefCircle().x;
	j["cy0"] = this->calibrationData->getRefCircle().y;
	j["dx"] = this->calibrationData->getGridSpacing()[0];
	j["dy"] = this->calibrationData->getGridSpacing()[1];
	j["error"] = this->calibrationData->getError();

	j["circles"] = nlohmann::json::array();
	for (auto& circle : this->calibrationData->getCircles())
	{
		j["circles"].push_back({ circle.x, circle.y });
	}
	
	// Save error heatmap
	// Convert cv::Mat to a vector of triple
	std::vector<uint8_t> errorHeatmapVec;
	if (!this->calibrationData->getErrorHeatmap().empty())
	{
		cv::Mat errorHeatmap = this->calibrationData->getErrorHeatmap();
		for (int i = 0; i < errorHeatmap.rows; i++)
		{
			for (int j = 0; j < errorHeatmap.cols; j++)
			{
				errorHeatmapVec.push_back(errorHeatmap.at<cv::Vec3b>(i, j)[0]);
				errorHeatmapVec.push_back(errorHeatmap.at<cv::Vec3b>(i, j)[1]);
				errorHeatmapVec.push_back(errorHeatmap.at<cv::Vec3b>(i, j)[2]);
			}
		}
		j["errorHeatmap"] = errorHeatmapVec;
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
	if (this->previewController->getIsPreviewOn())
	{
		this->previewController->stopPreview();
	}
	this->previewController->setFrame(&image);

	// Load calibration parameters
	CalibrationParametersDto param(
		cv::Size(j["gaussKernel"][0], j["gaussKernel"][1]),
		j["blockSize"],
		j["c"],
		j["clusterDistance"],
		j["useInvertImage"],
		j["drawCircles"],
		j["drawGrid"],
		j["aperture"]
	);
	this->calibrationEngine->setParameters(param);

	// Load calibration data
	std::vector<cv::Point2d> circles;
	for (auto& circle : j["circles"])
	{
		circles.push_back(cv::Point2d(circle[0], circle[1]));
	}
	
	// Load error heatmap
	std::vector<uint8_t> errorHeatmapVec = j["errorHeatmap"];
	cv::Mat errorHeatmap(cvImage.rows, cvImage.cols, CV_8UC3);
	int idx = 0;
	for (int i = 0; i < errorHeatmap.rows; i++)
	{
		for (int j = 0; j < errorHeatmap.cols; j++)
		{
			errorHeatmap.at<cv::Vec3b>(i, j)[0] = errorHeatmapVec[idx++];
			errorHeatmap.at<cv::Vec3b>(i, j)[1] = errorHeatmapVec[idx++];
			errorHeatmap.at<cv::Vec3b>(i, j)[2] = errorHeatmapVec[idx++];
		}
	}
	
	CalibrationData* calibData = new CalibrationData(cvImage, (double)j["cx0"], 
		(double)j["cy0"], (double)j["dx"], (double)j["dy"], (double)j["error"], errorHeatmap, circles);

	// Delete the previous calibration data & set the new one
	if (this->calibrationData != nullptr)
	{
		delete this->calibrationData;
		this->calibrationData = calibData;
	}
}

CalibrationData CalibrationController::GetCalibrationData()
{
	return *this->calibrationData;
}

void CalibrationController::storeCalibrationDataPair()
{
	CalibrationParametersDto param = this->calibrationEngine->getParameters();
	CalibrationData calibData = *this->calibrationData;
	this->calibrationDataList.push_back(std::make_pair(param, calibData));
}

void CalibrationController::deleteCalibrationDataList()
{
	this->calibrationDataList.clear();
}

CalibrationData CalibrationController::computeMeanResult(){
	if (this->calibrationDataList.empty())
	{
		this->handleError(-1, "No calibration data available");
		return CalibrationData();
	}

	// Compute the mean of the calibration data

	// Circles positions
	std::vector<cv::Point2d> meanCircles;
	for (int i = 0; i < this->calibrationDataList[0].second.getCircles().size(); i++)
	{
		double x = 0;
		double y = 0;
		for (auto& pair : this->calibrationDataList)
		{
			x += pair.second.getCircles()[i].x;
			y += pair.second.getCircles()[i].y;
		}
		x /= this->calibrationDataList.size();
		y /= this->calibrationDataList.size();
		meanCircles.push_back(cv::Point2d(x, y));
	}

	// Grid spacing
	double dx = 0;
	double dy = 0;
	for (auto& pair : this->calibrationDataList)
	{
		dx += pair.second.getGridSpacing()[0];
		dy += pair.second.getGridSpacing()[1];
	}
	dx /= this->calibrationDataList.size();
	dy /= this->calibrationDataList.size();

	// Image is the one of the calibration data with the minimal error
	CalibrationData meanCalibData = this->calibrationDataList[0].second;
	double minError = this->calibrationDataList[0].second.getError();
	for (auto& pair : this->calibrationDataList)
	{
		if (pair.second.getError() < minError)
		{
			minError = pair.second.getError();
			meanCalibData = pair.second;
		}
	}
	cv::Mat meanImage = meanCalibData.getImage();

	// Error and error heatmap is recomputed using CalibrationEngine
	Eigen::MatrixXd meanSolMatrix= Eigen::MatrixXd(4, 1);
	meanSolMatrix << meanCalibData.getRefCircle().x, meanCalibData.getRefCircle().y, dx, dy;
	Eigen::MatrixXd meanCircleMatrix = Eigen::MatrixXd(2 * meanCircles.size(), 1);
	for (int i = 0; i < meanCircles.size(); i++)
	{
		meanCircleMatrix(i, 0) = meanCircles[i].x;
		meanCircleMatrix(i + meanCircles.size(), 0) = meanCircles[i].y;
	}
	std::pair<double, std::vector<double>> meanError = this->calibrationEngine->computeMeanError(meanSolMatrix, meanCircleMatrix);
	cv::Mat meanErrorHeatmap = this->calibrationEngine->generateErrorHeatmap(meanCircles, meanError.second, meanImage, meanSolMatrix);

	// update ui

	this->calibrationData = new CalibrationData(meanImage, meanCalibData.getRefCircle().x, meanCalibData.getRefCircle().y, dx, dy,
		meanError.first, meanErrorHeatmap, meanCircles);

	this->updateImage(meanImage);

	return *calibrationData;
}
