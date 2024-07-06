#pragma once
#include <opencv2/opencv.hpp>
#include <string>

/**
 * @brief Data Transfer Object class for CalibrationParameters.
 * 
 * This class is used to transmit the parameters used on the calibration pipeline.
 * 
 */
class CalibrationParametersDto {
	//**Parameters**//

	/**
	 * @brief Aperture name used on the calibration.
	 * 
	 */
	std::string aperture;
	/**
	 * @brief If true, the image will be inverted before applying the threshold.
	 * 
	 */
	bool useInvertImage;
	/**
	 * @brief If true, the circles will be drawn on the image.
	 * 
	 */
	bool drawCircles;
	/**
	 * @brief If true, the grid will be drawn on the image.
	 * 
	 */
	bool drawGrid;

	/**
	 * @brief Kernel size for the Gaussian blur.
	 * 
	 */
	cv::Size gaussKernel;
	/**
	 * @brief Block size for the adaptive threshold.
	 * 
	 */
	int blockSize;
	/**
	 * @brief Constant subtracted from the mean used on the adaptive threshold.
	 * 
	 */
	double c;
	/**
	 * @brief Interval size where peaks are considered to be the same cluster.
	 * 
	 */
	double clusterDistance;
public:
	CalibrationParametersDto();
	CalibrationParametersDto(cv::Size gaussKernel, int blockSize, double c, double clusterDistance, bool useInvertImage = false, bool drawCircles = false, bool drawGrid = false, std::string apertureName = "");
	cv::Size getGaussKernel() const;
	int getBlockSize() const;
	double getC() const;
	double getClusterDistance() const;
	bool getUseInvertImage() const;
	bool getDrawCircles() const;
	bool getDrawGrid() const;
	std::string getAperture() const;
};
