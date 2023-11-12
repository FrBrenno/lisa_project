#include "ImageController.h"
#include "WFS.h"

ImageController::ImageController(bool is_wfs_connected, Instrument* instrument): BaseController(is_wfs_connected)
{
	this->instrument = instrument;
	this->err = 0;
	this->rows = 0;
	this->cols = 0;
	this->imageBuffer = NULL;
	this->cameraConfig = new CameraConfig();
	this->image = new wxImage();
}

void ImageController::takeImage(){
	//Verifies if the api is connected before taking an image, if not, it will return
	if (!this->is_wfs_connected) {
		this->handleError(-1, "WFS is not connected");
		return;
	}

	// It can only take an image if the instrument is initialized
	if (instrument->isInitialized()) {

		ViReal64* exposureTime = cameraConfig->getExposureTime();
		ViReal64* gain = cameraConfig->getGain();

		// Take a camera image with auto exposure
		for (int i = 0; i < cameraConfig->getNbImageReadings(); i++)
		{
			if (err = WFS_TakeSpotfieldImageAutoExpos(*instrument->getHandle(), exposureTime, gain)) {
				this->handleError(err, "Error while taking spotfield image");
			}
		}

		// TODO: Check instrument status for non-optimal image exposure

		// Get last image
		if (err =  WFS_GetSpotfieldImage(*instrument->getHandle(), &imageBuffer, &rows, &cols)) {
			this->handleError(err, "Error while getting spotfield image");
		}

		// Convert image buffer to wxImage
		this->image = new wxImage(cols, rows, imageBuffer, true);
	}
}

//=== Utility functions ===//

wxImage* ImageController::getImage()
{
	return this->image;
}

