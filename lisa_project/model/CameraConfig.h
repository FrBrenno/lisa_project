#include "WFS.h"

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

public:
	CameraConfig();
	CameraConfig(int cameraResolution, int exposureTime, int gain, int noiseCutLevel, int blackLevel, int nbImageReadings);

	int getCameraResolution();
	ViReal64* getExposureTime();
	ViReal64* getGain();
	int getNoiseCutLevel();
	int getBlackLevel();
	int getNbImageReadings();

	void setCameraConfig(int cameraResolution, int exposureTime, int gain, int noiseCutLevel, int blackLevel, int nbImageReadings);

};
