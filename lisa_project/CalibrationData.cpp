#include "CalibrationData.h"

CalibrationData::CalibrationData() {
	this->image = cv::Mat();
	this->gridSpacingX = 0;
	this->gridSpacingY = 0;
	this->circlesPositions = std::vector<cv::Point2d>();
}

CalibrationData::CalibrationData(cv::Mat modifiedImage, double gridSpacingX, double gridSpacingY, std::vector<cv::Point2d> circlesPositions) {
	this->image = modifiedImage;
	this->gridSpacingX = gridSpacingX;
	this->gridSpacingY = gridSpacingY;
	this->circlesPositions = circlesPositions;
}

cv::Mat CalibrationData::getImage() {
	return image;
}

std::vector<double> CalibrationData::getGridSpacing() {
	return { gridSpacingX, gridSpacingY };
}

std::vector<cv::Point2d> CalibrationData::getCirclesPositions() {
	return circlesPositions;
}


