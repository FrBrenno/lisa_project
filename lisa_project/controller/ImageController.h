#pragma once
#include "wx/wx.h"
#include "model/Dto/InstrumentDto.h"
#include "BaseController.h"
#include "event/InstrumentSelectedEvent.h"
#include <opencv2/opencv.hpp>

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController: public BaseController{
	Instrument* instrument;

	int err;
	ViAUInt8 imageBuffer;
	ViInt32 rows, cols;
	cv::Mat image;

	const int NUMBER_READING_IMAGES = 3;

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


	void HandleNewInstrumentSelected(InstrumentSelectedEvent event);
};
