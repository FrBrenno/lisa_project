#pragma once
#include "../controller/BaseController.h"
#include "../MyAppInterface.h"
#include <opencv2/opencv.hpp>

class ImageProcessingController: public BaseController
{
	cv::Mat* image;
	int rows, cols;
public:
	ImageProcessingController(MyAppInterface* main, WfsApiService* wfsApiService);

	void setImage(cv::Mat* image, int rows, int cols);

	void processImage();

	cv::Mat getProcessedImage();
};
