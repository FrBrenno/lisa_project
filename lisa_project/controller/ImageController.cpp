#include "ImageController.h"
#include "lib/thorlabs_api/WFS.h"
#include "../EventDispatcher.h"


ImageController::ImageController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->instrument = nullptr;
	this->err = 0;
	this->rows = 0;
	this->cols = 0;
	this->imageBuffer = VI_NULL;
	this->rgbBuffer = VI_NULL;
	this->image = new wxImage();
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
	delete[] rgbBuffer;
	delete[] imageBuffer;
	delete image;
	delete imageProcessingController;
}

void ImageController::takeImage(){

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
		// TODO: Maybe use opencv to do the convertion to RGB
		delete[] rgbBuffer;
		rgbBuffer = new unsigned char[3 * this->cols * this->rows];
		this->convertGrayscaleToRGB(imageBuffer, this->cols, this->rows, rgbBuffer); //use OpenCV to convert to RGB

		if (this->imageProcessingEnabled)
			// TODO: maybe keep the original image and only set the desirable one as output. (in order to all display grid or not in a static image.
			this->imageBuffer = this->imageProcessingController->processImage(this->imageBuffer, this->rows, this->cols);

		this->image->Destroy();
        this->image = new wxImage(cols, rows, rgbBuffer, true);
        // Check if the image creation was successful
        if (!this->image->IsOk()) {
			err = -1;
            this->handleError(-1, "Failed to create wxImage");
            return;
        }
	}

}


//=== Utility functions ===//
// TODO: replace with opencv function
void ImageController::convertGrayscaleToRGB(const unsigned char* grayscaleBuffer, int width, int height, unsigned char* rgbBuffer) {
	// Assuming your grayscaleBuffer contains width * height pixel values
	// Iterate through each pixel in the grayscale image
	for (int i = 0; i < width * height; ++i) {
		// Grayscale pixel value (0 to 255)
		unsigned char grayValue = grayscaleBuffer[i];

		// Copy the grayscale value to all three channels (RGB)
		rgbBuffer[3 * i] = grayValue;     // Red channel
		rgbBuffer[3 * i + 1] = grayValue; // Green channel
		rgbBuffer[3 * i + 2] = grayValue; // Blue channel
	}
}

// TODO: return th desirable image
wxImage* ImageController::getImage()
{
	if (this->image && this->image->IsOk()) {
		return this->image;
	}
	else {
		err = -1;
		this->handleError(-1, "Image is not ok");
		return nullptr;
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
