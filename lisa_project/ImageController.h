#pragma once
#include "wx/wx.h"
#include "CameraConfig.h"
#include "Instrument.h"

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController{
	CameraConfig* cameraConfig;
	Instrument* instrument;
	int err;
	unsigned char* imageBuffer;
	ViInt32 rows, cols;
	wxImage* image;

public:
	ImageController(Instrument* instrument);

	/**
	 * Returns a pointer the image buffer.
	 * 
	 */
	void takeImage();
	/**
	 * Handles error messages.
	 * 
	 * @param code Error code
	 * @param message Developer error message
	 */
	void handleError(int code, std::string message);

	/**
	 * Returns a pointer to the wxImage created from the image buffer given by the API.
	 * 
	 * @return wxImage* Reference to image object
	 */
	wxImage* getImage();
};
