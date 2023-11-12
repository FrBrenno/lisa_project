#pragma once
#include "wx/wx.h"
#include "CameraConfig.h"
#include "Instrument.h"
#include "BaseController.h"

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController: public BaseController{
	CameraConfig* cameraConfig;
	Instrument* instrument;
	int err;
	unsigned char* imageBuffer;
	ViInt32 rows, cols;
	wxImage* image;

public:
	ImageController(bool is_wfs_connected, Instrument* instrument);

	/**
	 * Returns a pointer the image buffer.
	 * 
	 */
	void takeImage();

	/**
	 * Returns a pointer to the wxImage created from the image buffer given by the API.
	 * 
	 * @return wxImage* Reference to image object
	 */
	wxImage* getImage();
};
