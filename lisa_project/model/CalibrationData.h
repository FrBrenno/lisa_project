#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class CalibrationData {
    cv::Mat image;
    double cx0;
    double cy0;
    double gridSpacingX;
    double gridSpacingY;
    double error;
	cv::Mat errorHeatmap;
    std::vector<cv::Point2d> circles;

public:
    CalibrationData();
    CalibrationData(cv::Mat modifiedImage, double cx0, double cy0, double gridSpacingX, double gridSpacingY, double error, cv::Mat errorHeatmap, std::vector<cv::Point2d> circles);

    cv::Mat getImage();
    cv::Point2d getRefCircle();
    std::vector<double> getGridSpacing();
    double getError();
	cv::Mat getErrorHeatmap();
    std::vector<cv::Point2d> getCircles();
};