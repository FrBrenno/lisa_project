#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class CalibrationData {
    cv::Mat image;
    double gridSpacingX;
    double gridSpacingY;
    std::vector<cv::Point2d> circlesPositions;
public:
    CalibrationData();
    CalibrationData(cv::Mat modifiedImage, double gridSpacingX, double gridSpacingY, std::vector<cv::Point2d> circlesPositions);

    cv::Mat getImage();
    std::vector<double> getGridSpacing();
    std::vector<cv::Point2d> getCirclesPositions();
};