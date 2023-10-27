#pragma once

class CameraSettings{
	int cameraResolution;
	int exposureTime;
	int gain;
	int noiseCutLevel;
	int blackLevel;

public:
	CameraSettings();
	CameraSettings(int cameraResolution, int exposureTime, int gain, int noiseCutLevel, int blackLevel);
	~CameraSettings();

	int getCameraResolution();
	int getExposureTime();
	int getGain();
	int getNoiseCutLevel();
	int getBlackLevel();

	void setCameraResolution(int cameraResolution);
	void setExposureTime(int exposureTime);
	void setGain(int gain);
	void setNoiseCutLevel(int noiseCutLevel);
	void setBlackLevel(int blackLevel);

};
