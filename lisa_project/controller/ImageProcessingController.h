#pragma once
#include "../controller/BaseController.h"
#include "../MyAppInterface.h"
#include <opencv2/opencv.hpp>

class ImageProcessingController: public BaseController
{
public:
	ImageProcessingController(MyAppInterface* main, WfsApiService* wfsApiService);

	unsigned char* processImage(unsigned char* image_buffer, int rows, int cols);
};
