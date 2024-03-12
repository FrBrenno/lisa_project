#pragma once
#include "wx/wx.h"
#include "model/Dto/InstrumentDto.h"
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
	ViAUInt8 imageBuffer;
	ViInt32 rows, cols;
	cv::Mat image;

	bool imageProcessingEnabled;
	const int NUMBER_READING_IMAGES = 5;

public:
	ImageController(MyAppInterface* main, IApiService* wfsApiService);
	~ImageController();
	/**
	 * Returns a pointer the image buffer.
	 * 
	 */
	void acquireImage();

	/**
	 * Returns a pointer to the wxImage created from the image buffer given by the API.
	 * 
	 * @return wxBitmap* Reference to the wxBitmap created from the image buffer.
	 */
	wxImage* getImage();


	void HandleNewInstrumentSelected(Instrument* instrument);
};
