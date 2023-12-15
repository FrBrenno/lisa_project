#pragma once
#include "../controller/BaseController.h"
#include "../MyAppInterface.h"
#include <opencv2/opencv.hpp>

class ImageProcessingController: public BaseController
{
	cv::Mat image;

	void edgeDetection();
public:
	ImageProcessingController(MyAppInterface* main, bool is_wfs_connected, unsigned char* image_buffer, int row, int col);

	void processImage(unsigned char* image_buffer, int rows, int cols);
};
