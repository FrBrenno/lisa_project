#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class CalibrationParametersDto {
	bool useInvertImage;
	bool drawCircles;
	bool drawGrid;
	std::string apertureName;

	cv::Size gaussKernel;
	int blockSize;
	double c;
	double clusterDistance;
public:
	CalibrationParametersDto();
	CalibrationParametersDto(cv::Size gaussKernel, int blockSize, double c, double clusterDistance, bool useInvertImage = false, bool drawCircles = false, bool drawGrid = false, std::string apertureName);
	cv::Size getGaussKernel() const;
	int getBlockSize() const;
	double getC() const;
	double getClusterDistance() const;
	bool getUseInvertImage() const;
	bool getDrawCircles() const;
	bool getDrawGrid() const;
	std::string getApertureName() const;
};
