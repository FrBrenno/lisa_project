#include "ImageProcessingController.h"

ImageProcessingController::ImageProcessingController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{}

void ImageProcessingController::setImage(cv::Mat* image, int rows, int cols)
{
	this->image = image;
	this->rows = rows;
	this->cols = cols;
}

void ImageProcessingController::processImage()
{
}

cv::Mat ImageProcessingController::getProcessedImage()
{
	return this->image->clone();
}
