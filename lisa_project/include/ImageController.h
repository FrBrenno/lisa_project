#pragma once
#include "wx/wx.h"
#include "InstrumentDto.h"
#include "BaseController.h"
#include "InstrumentSelectedEvent.h"
#include <opencv2/opencv.hpp>

/**
 * @class ImageController.
 * @brief This controller handles image acquisition. 
 */
class ImageController: public BaseController{
	/**
	 * @brief Instrument object.
	 * 
	 */
	Instrument* instrument;

	/**
	 * @brief Flag that indicates if the instrument is connected.
	 * 
	 */
	int err;
	/**
	 * @brief Image buffer.
	 * 
	 */
	ViAUInt8 imageBuffer;
	/**
	 * @brief Image buffer size.
	 * 
	 */
	ViInt32 rows, cols;
	/**
	 * @brief Image converted to a matrix.
	 * 
	 */
	cv::Mat image;

	/**
	 * @brief constant that indicates the number of images to be read before capturing the image.
	 * 
	 */
	const int NUMBER_READING_IMAGES = 3;

public:
	ImageController(MyAppInterface* main, IApiService* wfsApiService);
	~ImageController();
	
	/**
	 * @brief Acquires the image from the instrument.
	 * 
	 * It calls the API to acquire the image from the instrument. 
	 * Then, the image is converted to a cv::Mat object, flipped and converted to grayscale.
	 */
	void acquireImage();

	/**
	 * @brief Returns a pointer to the wxImage created from the image buffer given by the API.
	 * 
	 * @return wxBitmap* Reference to the wxBitmap created from the image buffer.
	 */
	wxImage* getImage();

	/**
	 * @brief Handles the selection of a new instrument.
	 * 
	 * It receives the event and updates the instrument object.
	 * 
	 * @param event InstrumentSelectedEvent object.
	 */
	void HandleNewInstrumentSelected(InstrumentSelectedEvent event);
};
