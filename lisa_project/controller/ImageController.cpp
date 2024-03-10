#include "ImageController.h"
#include "lib/thorlabs_api/WFS.h"
#include "../EventDispatcher.h"
#include <opencv2/opencv.hpp>

ImageController::ImageController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->instrument = nullptr;
	this->err = 0;
	this->rows = 0;
	this->cols = 0;
	this->imageBuffer = VI_NULL;
	this->image = cv::Mat();
	this->imageProcessingController = new ImageProcessingController(this->app, this->wfsApiService);
	this->imageProcessingEnabled = true;

	EventDispatcher::Instance().SubscribeToEvent("NewInstrumentSelected",
		[this](const Event& event) {
			Instrument* instrument = (Instrument*) event.getData();
			HandleNewInstrumentSelected(instrument);
		});
}

ImageController::~ImageController()
{
	delete[] imageBuffer;
	delete imageProcessingController;
}

void ImageController::acquireImage(){

	//Verifies if the api is connected before taking an image, if not, it will return
	if (!this->isWfsConnected()) {
		// Call to main so it can try to connect to API
		err = -1;
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// It can only take an image if the instrument is initialized
	if (instrument->isInitialized()) {
		this->wfsApiService->getImage(this->instrument->getHandle(), this->NUMBER_READING_IMAGES,
			&this->imageBuffer, &this->rows, &this->cols);
		
		// Convert black and white image buffer to RGB image buffer
		this->image = cv::Mat(this->rows, this->cols, CV_8UC1, this->imageBuffer);
		cv::cvtColor(this->image, this->image, cv::COLOR_GRAY2RGB);

		if (this->imageProcessingEnabled)
		{
			this->imageProcessingController->setImage(&this->image, this->rows, this->cols);
			this->imageProcessingController->calibrationPipeline();
		}
	}

}


//=== Utility functions ===//

// TODO: return th desirable image
wxImage* ImageController::getImage()
{
	if (this->err != 0) {
		this->handleError(this->err, "Error taking image");
		return nullptr;
	}

	if (this->imageProcessingEnabled)
	{
		cv::Mat processedImage = this->imageProcessingController->getProcessedImage();
		wxImage* image = new wxImage(processedImage.cols, processedImage.rows,
			processedImage.data, true);
		if (image->IsOk()) {
			return image;
		}
		else {
			this->handleError(-1, "Error creating wxImage");
			return nullptr;
		}
	}
	else
	{
		wxImage* image = new wxImage(this->image.cols, this->image.rows,
						this->image.data, true);
		if (image->IsOk()) {
			return image;
		}
		else {
			this->handleError(-1, "Error creating wxImage");
			return nullptr;
		}
	}
}


//=== Event Handlers ===//

void ImageController::HandleNewInstrumentSelected(Instrument* instrument)
{
	if (instrument == nullptr) {
		err = -1;
		this->handleError(-1, "Instrument is null");
		return;
	}

	if (this->instrument != nullptr) {
		delete this->instrument;
	}

	this->instrument = instrument;
	if (this->instrument->isInitialized()) {
		this->err = 0;
	}
	else {
		this->err = -1;
		this->handleError(-1, "Instrument is not initialized");
	}
}
