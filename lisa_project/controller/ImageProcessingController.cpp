#include "ImageProcessingController.h"

ImageProcessingController::ImageProcessingController(MyAppInterface* main, bool is_wfs_connected, unsigned char* image_buffer, int rows, int cols) : BaseController(main, is_wfs_connected)
{
	this->image = cv::Mat(rows, cols, CV_8UC1, image_buffer);
}

void ImageProcessingController::processImage(unsigned char* image_buffer, int rows, int cols)
{
	// create cv::Mat from image_buffer
	this->image = cv::Mat(rows, cols, CV_8UC1, image_buffer);
	edgeDetection();
}

void ImageProcessingController::edgeDetection()
{
	cv::Mat edges;
	cv::Canny(this->image, edges, 100, 200);
	cv::imshow("edges", edges);
	cv::waitKey(0);
}
