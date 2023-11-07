#pragma once
#include "wx/wx.h"
#include "CameraConfig.h"
#include "Instrument.h"

class ImageController{
	CameraConfig* cameraConfig;
	Instrument* instrument;
	int err;
	unsigned char* imageBuffer;
	ViInt32 rows, cols;
	wxImage* image;

public:
	ImageController(Instrument* instrument);

	void takeImage();
	void handleError(int code, std::string message);

	wxImage* getImage();
};
