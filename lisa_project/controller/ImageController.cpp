#include "ImageController.h"
#include "lib/thorlabs_api/WFS.h"
#include "../event/EventDispatcher.h"
#include "CalibrationEngine.h"
#include <opencv2/opencv.hpp>

ImageController::ImageController(MyAppInterface* main, IApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->instrument = nullptr;
	this->err = 0;
	this->rows = 0;
	this->cols = 0;
	this->imageBuffer = VI_NULL;
	this->image = cv::Mat();

	EventDispatcher::Instance().SubscribeToEvent<InstrumentSelectedEvent>(
		[this](const InstrumentSelectedEvent& event) {
			HandleNewInstrumentSelected(event);
		});
}

ImageController::~ImageController()
{
	delete[] imageBuffer;
}

void ImageController::acquireImage() {
    // Verifies if the API is connected before taking an image, if not, it will return
    if (!this->wfsApiService->isApiConnectionActive()) {
        // Call to main so it can try to connect to API
        err = -1;
        this->handleError(-1, "WFS is not connected");
        return;
    }

    // It can only take an image if the instrument is initialized
    if (instrument->isInitialized()) {
        // If the image buffer is not null, it means that it has already taken an image
        if (this->imageBuffer != VI_NULL) {
            // Delete the previously allocated memory
            delete[] this->imageBuffer;
            this->imageBuffer = VI_NULL; // Set to NULL after deletion
        }

        ViStatus status;
        status = this->wfsApiService->getImage(
            this->instrument->getHandle(),
            this->NUMBER_READING_IMAGES,
            &this->imageBuffer,
            &this->rows,
            &this->cols);

        if (status != VI_SUCCESS) {
            // Handle error, but do not delete imageBuffer as it was not allocated successfully
            this->handleError(status, "Error taking image");
            return;
        }

        // Ensure that imageBuffer is not NULL
        if (this->imageBuffer != VI_NULL) {
            // Create cv::Mat using the acquired imageBuffer
            this->image = cv::Mat(this->rows, this->cols, CV_8UC1, this->imageBuffer);
            // Flip the image (it is upside down)
            cv::flip(this->image, this->image, 0);
            // Convert black and white image buffer to RGB image buffer
            cv::cvtColor(this->image, this->image, cv::COLOR_GRAY2RGB);
        }
    }
}



//=== Utility functions ===//

// TODO: return th desirable image
wxImage* ImageController::getImage() {
    if (this->err != 0) {
        this->handleError(this->err, "Error taking image");
        return nullptr;
    }

    wxImage* image = new wxImage(cols, rows, this->image.data, true);
    if (image->IsOk()) {
        return image;
    }
    else {
        this->handleError(-1, "Error creating wxImage");
        delete image; // Clean up the allocated memory
        return nullptr;
    }
}



//=== Event Handlers ===//

void ImageController::HandleNewInstrumentSelected(InstrumentSelectedEvent event)
{
	Instrument* instrument = event.getData();
	this->instrument = instrument;
}
