#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

/**
 **	@class CalibrationData.
 ** @brief Data object containing the calibration data.
 ** @details This class is responsible for storing the calibration data acquired during the calibration process.
 **/
class CalibrationData {
    /**
     * @brief image: The image acquired during the calibration process.
     * 
     */
    cv::Mat image;
    /**
     * @brief cx0: The x coordinate of the reference circle.
     * 
     */
    double cx0;
    /**
     * @brief cy0: The y coordinate of the reference circle.
     * 
     */
    double cy0;
    /**
     * @brief gridSpacingX: The grid spacing in the x direction.
     * 
     */
    double gridSpacingX;
    /**
     * @brief gridSpacingY: The grid spacing in the y direction.
     * 
     */
    double gridSpacingY;
    /**
     * @brief error: The error of the calibration.
     * 
     */
    double error;
    /**
     * @brief errorHeatmap: The heatmap of the error.
     * 
     */
	cv::Mat errorHeatmap;
    /**
     * @brief circles: The circles detected in the calibration frame.
     * 
     */
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