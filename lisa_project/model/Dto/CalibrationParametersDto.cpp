#include "CalibrationParametersDto.h"

CalibrationParametersDto::CalibrationParametersDto(cv::Size gaussKernel, int blockSize, double c, double clusterDistance) {
	this->gaussKernel = gaussKernel;
	this->blockSize = blockSize;
	this->c = c;
	this->clusterDistance = clusterDistance;
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
