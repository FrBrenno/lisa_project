#include "ImageProcessingController.h"

ImageProcessingController::ImageProcessingController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{
	this->image = nullptr;
	this->rows = 0;
	this->cols = 0;

	this->gauss_kernel_size = 15;
	this->block_size = 31;
	this->c = 3;
	this->clustering_distance = 3;
}

void ImageProcessingController::setImage(cv::Mat* image, int rows, int cols)
{
	this->image = image;
	this->rows = rows;
	this->cols = cols;
}

cv::Mat ImageProcessingController::getProcessedImage()
{
	return this->image->clone();
}

void ImageProcessingController::calibrationPipeline()
{
	cv::Mat thresh = generateThresholdImage();
	
}

cv::Mat ImageProcessingController::generateThresholdImage()
{
	// Convert to gray
	cv::Mat result;
	cv::cvtColor(*this->image, result, cv::COLOR_BGR2GRAY);
	
	// Apply GaussianBlur
	cv::GaussianBlur(result, result, 
		cv::Size(this->gauss_kernel_size, this->gauss_kernel_size), 0);

	// Apply adaptiveThreshold
	/* 
	Apply adaptive thresholding using mean of neighborhood as the threshold value
    Pixels with values above the threshold become white, and below become black
	*/
	cv::adaptiveThreshold(result, result, 255, cv::ADAPTIVE_THRESH_MEAN_C,
		cv::THRESH_BINARY, this->block_size, this->c);

	return result;
}
