#include "CalibrationController.h"
#include "EventDispatcher.h"
#include "CalibrationStartEvent.h"
#include "CalibrationDialog.h"
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <regex>

#define CONVERSION_PX_microM 5

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
	if (!std::regex_match(apertureName, std::regex("^[a-zA-Z0-9_./,;:-]*$")))
	{
		errors |= 0x10; // 0001 0000
	}
	
	return errors;
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

CalibrationData CalibrationController::computeGlobalResult(){
	if (this->calibrationDataList.empty())
	{
		this->handleError(-1, "No calibration data available");
		return CalibrationData();
	}

	//=== Compute the global of the calibration data

	// Collect the index of the calibration with the least error

	double minError = this->calibrationDataList[0].second.getError();
	int minErrorIndex = 0;
	for (int i = 1; i < this->calibrationDataList.size(); i++)
	{
		if (this->calibrationDataList[i].second.getError() < minError)
		{
			minError = this->calibrationDataList[i].second.getError();
			minErrorIndex = i;
		}
	}

	// Global circle positions are the circles positions of the calibration with the least error
	std::vector<cv::Point2d> globalCircles = this->calibrationDataList[minErrorIndex].second.getCircles();

	// Global result image is the image of the calibration with the least error
	cv::Mat globalImage = this->calibrationDataList[minErrorIndex].second.getImage();

	// Global reference circle is the one of the calibration with the least error
	cv::Point2d globalRefCircle = this->calibrationDataList[minErrorIndex].second.getRefCircle();

	// Mean Grid spacing
	double meanDx = 0;
	double meanDy = 0;
	for (auto& pair : this->calibrationDataList)
	{
		meanDx += pair.second.getGridSpacing()[0];
		meanDy += pair.second.getGridSpacing()[1];
	}
	meanDx /= this->calibrationDataList.size();
	meanDy /= this->calibrationDataList.size();


	//=== Compute mean error and error heatmap

	// Set new mean solution matrix
	Eigen::MatrixXd meanSolMatrix= Eigen::MatrixXd(4, 1);
	meanSolMatrix << globalRefCircle.x, globalRefCircle.y, meanDx, meanDy;

	// Reconstruct matrix B
	Eigen::MatrixXd globalCircleMatrix = Eigen::MatrixXd(2 * globalCircles.size(), 1);
	for (int i = 0; i < globalCircles.size(); i++)
	{
		globalCircleMatrix(i, 0) = globalCircles[i].x;
		globalCircleMatrix(i + globalCircles.size(), 0) = globalCircles[i].y;
	}
	// Compute mean and the heatmap using the engine
	std::pair<double, std::vector<double>> meanError = this->calibrationEngine->computeMeanError(meanSolMatrix, globalCircleMatrix);
	cv::Mat meanErrorHeatmap = this->calibrationEngine->generateErrorHeatmap(globalCircles, meanError.second, globalImage, meanSolMatrix);

	// update ui
	this->calibrationData = new CalibrationData(globalImage, globalRefCircle.x, globalRefCircle.y, meanDx, meanDy,
		meanError.first, meanErrorHeatmap, globalCircles);

	return *calibrationData;
}

float CalibrationController::computeDiameter(CalibrationData calibData) {
	float dx = calibData.getGridSpacing()[0];
	float dy = calibData.getGridSpacing()[1];
	return (dx + dy) / 2 * CONVERSION_PX_microM;
}



nlohmann::ordered_json CalibrationController::constructCalibrationJson(CalibrationParametersDto param, CalibrationData calibData, bool writeParam)
{
	nlohmann::ordered_json j;

	if (writeParam) {
		j["gaussKernel"] = { param.getGaussKernel().width, param.getGaussKernel().height };
		j["blockSize"] = param.getBlockSize();
		j["c"] = param.getC();
		j["clusterDistance"] = param.getClusterDistance();
		j["useInvertImage"] = param.getUseInvertImage();
		j["drawCircles"] = param.getDrawCircles();
		j["drawGrid"] = param.getDrawGrid();
		j["aperture"] = param.getAperture();
	}
	// the image should be added to json in the higher level because path is needed.
	j["cx0 [px]"] = calibData.getRefCircle().x;
	j["cy0 [px]"] = calibData.getRefCircle().y;
	j["dx [px]"] = calibData.getGridSpacing()[0];
	j["dy [px]"] = calibData.getGridSpacing()[1];
	j["diameter [ux]"] = computeDiameter(calibData);
	j["error [px]"] = calibData.getError();

	j["circles"] = nlohmann::ordered_json::array();
	for (auto& circle : calibData.getCircles())
	{
		j["circles"].push_back({ circle.x, circle.y });
	}

	return j;
}

void CalibrationController::SaveCalibrationData(std::string path)
{
	// Gather all information to save: calibration parameters, calibration data
	CalibrationParametersDto param = this->calibrationEngine->getParameters();

	// Save image next to the calibration data
	std::string imagePath = path + ".png";
	cv::Mat cvImage(this->lastCalibrationFrame->GetHeight(), this->lastCalibrationFrame->GetWidth(), CV_8UC3, this->lastCalibrationFrame->GetData());
	cv::imwrite(imagePath, cvImage);

	// create json	
	nlohmann::ordered_json j = this->constructCalibrationJson(param, *this->calibrationData, true);
	j["image"] = imagePath;

	// Save to file
	std::ofstream file(path);
	file << j.dump(4);
	file.close();

}

void CalibrationController::saveCalibrationDataListFile(std::string path) {
	// Construct a json where the main object is the mean result saved in the calibrationData attribute
	// the others objects are the calibrationDataList

	// Save the mean result
	nlohmann::ordered_json j = this->constructCalibrationJson(CalibrationParametersDto(), *this->calibrationData, false);

	// Save image
	std::string imagePath = path + "_calibData_meanResult.png";
	cv::imwrite(imagePath, this->calibrationData->getImage());
	j["image"] = imagePath;

	// save calibration data list
	j["calibrationDataList"] = nlohmann::json::array();

	for (auto& pair : this->calibrationDataList)
	{
		nlohmann::json calibDataJson = this->constructCalibrationJson(pair.first, pair.second, true);
		// Save image next to the calibration data
		std::string imagePath = path + "_calibData_" + std::to_string(&pair - &this->calibrationDataList[0]) + ".png";
		cv::imwrite(imagePath, pair.second.getImage());
		calibDataJson["image"] = imagePath;

		j["calibrationDataList"].push_back(calibDataJson);
	}

	// Save to file
	std::ofstream file(path);
	file << j.dump(4);
	file.close();
}