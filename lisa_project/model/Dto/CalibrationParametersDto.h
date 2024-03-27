#pragma once
#include <opencv2/opencv.hpp>

class CalibrationParametersDto {
	cv::Size gaussKernel;
	int blockSize;
	double c;
	double clusterDistance;
public:
	CalibrationParametersDto(cv::Size gaussKernel, int blockSize, double c, double clusterDistance);
	cv::Size getGaussKernel() const;
	int getBlockSize() const;
	double getC() const;
	double getClusterDistance() const;
};
