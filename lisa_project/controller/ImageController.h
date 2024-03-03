#pragma once
#include "wx/wx.h"
#include "model/Instrument.h"
#include "controller/ImageProcessingController.h"
#include "BaseController.h"

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController: public BaseController{
	ImageProcessingController* imageProcessingController;

	Instrument* instrument;

	int err;
	ViAUInt8 imageBuffer, rgbBuffer;
	ViInt32 rows, cols;
	wxImage* image;

	bool imageProcessingEnabled;
	const int NUMBER_READING_IMAGES = 5;

	void convertGrayscaleToRGB(const unsigned char* grayscaleBuffer, int width, int height, unsigned char* rgbBuffer);
public:
	ImageController(MyAppInterface* main, WfsApiService* wfsApiService, Instrument* instrument);
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
