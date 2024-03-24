#include "CalibrationData.h"

CalibrationData::CalibrationData() {
	this->image = cv::Mat();
	this->cx0 = 0;
	this->cy0 = 0;
	this->gridSpacingX = 0;
	this->gridSpacingY = 0;
	this->circles = std::vector<cv::Point2d>();
}

CalibrationData::CalibrationData(cv::Mat image, double cx0, double cy0, double gridSpacingX, double gridSpacingY, std::vector<cv::Point2d> circles) {
	this->image = image;
	this->cx0 = cx0;
	this->cy0 = cy0;
	this->gridSpacingX = gridSpacingX;
	this->gridSpacingY = gridSpacingY;
	this->circles = circles;
}

cv::Mat CalibrationData::getImage() {
	return image;
}

cv::Point2d CalibrationData::getRefCircle() {
	return cv::Point2d(cx0, cy0);
}

std::vector<double> CalibrationData::getGridSpacing() {
	return { gridSpacingX, gridSpacingY };
}

std::vector<cv::Point2d> CalibrationData::getCircles() {
	return circles;
}


