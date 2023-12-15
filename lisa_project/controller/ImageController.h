#pragma once
#include "wx/wx.h"
#include "model/CameraConfig.h"
#include "model/Instrument.h"
#include "controller/CameraSettingsController.h"
#include "controller/ImageProcessingController.h"
#include "BaseController.h"

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController: public BaseController{
	CameraSettingsController* cameraSettingsController;
	ImageProcessingController* imageProcessingController;

	CameraConfig* cameraConfig;
	Instrument* instrument;

	int err;
	ViAUInt8 imageBuffer, rgbBuffer;
	ViInt32 rows, cols;
	wxImage* image;

	bool imageProcessingEnabled;

	void convertGrayscaleToRGB(const unsigned char* grayscaleBuffer, int width, int height, unsigned char* rgbBuffer);
public:
	ImageController(MyAppInterface* main, bool is_wfs_connected, Instrument* instrument);
	~ImageController();
	/**
	 * Returns a pointer the image buffer.
	 * 
	 */
	void takeImage();

	/**
	 * Returns a pointer to the wxImage created from the image buffer given by the API.
	 * 
	 * @return wxBitmap* Reference to the wxBitmap created from the image buffer.
	 */
	wxImage* getImage();

	int hasError() const;
};
