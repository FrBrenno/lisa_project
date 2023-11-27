#include "CameraConfig.h"
#include "Settings.h"

CameraConfig::CameraConfig() {
	// Default Values 
	this->cameraResolution = SAMPLE_CAMERA_RESOL_WFS20;
	this->nbImageReadings = SAMPLE_IMAGE_READINGS;
	this->blackLevel = 0;
	// To be set automatically by the API
	this->noiseCutLevel = 0;
	this->exposureTime = 0;
	this->gain = 0;
}

CameraConfig::CameraConfig(int cameraResolution, int exposureTime, int gain, int noiseCutLevel, int blackLevel, int nbImageReadings) {
	this->cameraResolution = cameraResolution;
	this->exposureTime = exposureTime;
	this->gain = gain;
	this->noiseCutLevel = noiseCutLevel;
	this->blackLevel = blackLevel;
	this->nbImageReadings = nbImageReadings;
}


int CameraConfig::getCameraResolution(){
	return this->cameraResolution;
}

ViReal64* CameraConfig::getExposureTime() {
	return &this->exposureTime;
}

ViReal64* CameraConfig::getGain() {
	return &this->gain;
}

int CameraConfig::getNoiseCutLevel() {
	return this->noiseCutLevel;
}

int CameraConfig::getBlackLevel() {
	return this->blackLevel;
}

int CameraConfig::getNbImageReadings() {
	return this->nbImageReadings;
}

void CameraConfig::setCameraConfig(int cameraResolution, int exposureTime, int gain, int noiseCutLevel, int blackLevel, int nbImageReadings) {
	this->cameraResolution = cameraResolution;
	this->exposureTime = exposureTime;
	this->gain = gain;
	this->noiseCutLevel = noiseCutLevel;
	this->blackLevel = blackLevel;
}
