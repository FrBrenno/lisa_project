#pragma once
#include "wx/wx.h"
#include "../model/CameraConfig.h"
#include "../model/Instrument.h"
#include "BaseController.h"

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController: public BaseController{
	CameraConfig* cameraConfig;
	Instrument* instrument;
	int err;
	ViAUInt8 imageBuffer, rgbBuffer;
	ViInt32 rows, cols;
	wxImage* image;

	void convertGrayscaleToRGB(const unsigned char* grayscaleBuffer, int width, int height, unsigned char* rgbBuffer);
public:
	ImageController(MyApp* app, bool is_wfs_connected, Instrument* instrument);

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
	wxBitmap* getBitmap();
};
