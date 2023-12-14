#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H

#include "lib/thorlabs_api/WFS.h"

/**
 * @class CameraConfig.
 * @brief This model class contains all the information about the camera configuration.
 */
class CameraConfig{
	int cameraResolution;
	ViReal64 exposureTime;
	ViReal64 gain;
	int noiseCutLevel;
	int blackLevel;
	int nbImageReadings;

	bool autoExposure;
	bool autoGain;
	bool autoNoiseCutLevel;
	bool autoBlackLevel;

public:
	CameraConfig();

	int getCameraResolution();
	ViReal64* getExposureTime();
	ViReal64* getGain();
	int getNoiseCutLevel();
	int getBlackLevel();
	int getNbImageReadings();
	bool isAutoExposure();
	bool isAutoGain();
	bool isAutoNoiseCutLevel();
	bool isAutoBlackLevel();


	void setCameraConfig(int cameraResolution, 
		int exposureTime, 
		int gain, 
		int noiseCutLevel, 
		int blackLevel, 
		int nbImageReadings,
		bool autoExposure,
		bool autoGain,
		bool autoNoiseCutLevel,
		bool autoBlackLevel);

	void setDefault();
};

#endif