#include "CalibrationParametersDto.h"
CalibrationParametersDto::CalibrationParametersDto() :
	gaussKernel(cv::Size(0, 0)),
	blockSize(0),
	c(0.0),
	clusterDistance(0.0),
	useInvertImage(false),
	drawCircles(false),
	drawGrid(false),
	aperture("")
{}

CalibrationParametersDto::CalibrationParametersDto(cv::Size gaussKernel, int blockSize, double c, double clusterDistance, 
	bool useInvertImage, bool drawCircles, bool drawGrid, std::string apertureName) {
	this->gaussKernel = gaussKernel;
	this->blockSize = blockSize;
	this->c = c;
	this->clusterDistance = clusterDistance;
	this->useInvertImage = useInvertImage;
	this->drawCircles = drawCircles;
	this->drawGrid = drawGrid;
	this->aperture = apertureName;
}

cv::Size CalibrationParametersDto::getGaussKernel() const {
	return gaussKernel;
}

int CalibrationParametersDto::getBlockSize() const {
	return blockSize;
}

double CalibrationParametersDto::getC() const {
	return c;
}

double CalibrationParametersDto::getClusterDistance() const {
	return clusterDistance;
}

bool CalibrationParametersDto::getUseInvertImage() const {
	return useInvertImage;
}

bool CalibrationParametersDto::getDrawCircles() const {
	return drawCircles;
}

bool CalibrationParametersDto::getDrawGrid() const {
	return drawGrid;
}

std::string CalibrationParametersDto::getAperture() const {
	return aperture;
}
