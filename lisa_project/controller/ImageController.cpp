#include "ImageController.h"
#include "WFS.h"

ImageController::ImageController(MyApp* app, bool is_wfs_connected, Instrument* instrument) : BaseController(app, is_wfs_connected)
{
	this->instrument = instrument;
	this->err = 0;
	this->rows = 0;
	this->cols = 0;
	this->imageBuffer = VI_NULL;
	this->rgbBuffer = VI_NULL;
	this->cameraConfig = new CameraConfig();
	this->image = new wxImage();
}

void ImageController::takeImage(){
	//Verifies if the api is connected before taking an image, if not, it will return
	isApiConnected();

	// It can only take an image if the instrument is initialized
	if (instrument->isInitialized()) {

		ViReal64* exposureTime = cameraConfig->getExposureTime();
		ViReal64* gain = cameraConfig->getGain();

		// Take a camera image with auto exposure
		for (int i = 0; i < cameraConfig->getNbImageReadings(); i++)
		{
			if (err = WFS_TakeSpotfieldImageAutoExpos(*instrument->getHandle(), exposureTime, gain)) {
				this->handleError(err, "Error while taking spotfield image");
				return;
			}
			ViInt32 status = VI_NULL;
			if (err = WFS_GetStatus(*instrument->getHandle(), &status))
				this->handleError(err, "Error while getting instrument status");
			if (instrument->getStatus() & WFS_STATBIT_PTH)
				this->handleError(-1, "Image exposure is too high");
			else if (instrument->getStatus() & WFS_STATBIT_PTL)
				this->handleError(-1, "Image exposure is too low");
			else if (instrument->getStatus() & WFS_STATBIT_HAL)
				this->handleError(-1, "Image gain is too high");
			else
			{
				cameraConfig->setCameraConfig(cameraConfig->getCameraResolution(), 
					*exposureTime, 
					*gain, 
					cameraConfig->getNoiseCutLevel(), 
					cameraConfig->getBlackLevel(), 
					cameraConfig->getNbImageReadings());
			}
		}

		// Get last image
        if (err = WFS_GetSpotfieldImage(*instrument->getHandle(), &imageBuffer, &rows, &cols)) {
            this->handleError(err, "Error while getting spotfield image");
            return;
        }

        // Convert image buffer to wxImage
		rgbBuffer = new unsigned char[3 * this->cols * this->rows];
		this->convertGrayscaleToRGB(imageBuffer, this->cols, this->rows, rgbBuffer);

        this->image = new wxImage(cols, rows, rgbBuffer, true);

        // Check if the image creation was successful
        if (!this->image->IsOk()) {
            this->handleError(-1, "Failed to create wxImage");
            return;
        }
		   
	}
}

//=== Utility functions ===//

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


wxBitmap* ImageController::getBitmap()
{
	if (this->image && this->image->IsOk()) {
		wxBitmap* capturedImg = new wxBitmap(*this->image);
		return capturedImg;
	}
}

