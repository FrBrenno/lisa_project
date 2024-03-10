#pragma once
#include "../controller/BaseController.h"
#include "../MyAppInterface.h"
#include <opencv2/opencv.hpp>

class ImageProcessingController: public BaseController
{
	cv::Mat* image;
	int rows, cols;

	int gauss_kernel_size;		// determines the size of the kernel
	int block_size;				// determines the size of the neighbourhood area
	int c;						//is a constant that is subtracted from the mean or weighted sum of the neighbourhood pixels.
	int clustering_distance;	// determines the distance threshold for the clustering algorithm

	cv::Mat generateThresholdImage();

public:
	ImageProcessingController(MyAppInterface* main, WfsApiService* wfsApiService);

	void setImage(cv::Mat* image, int rows, int cols);
	cv::Mat getProcessedImage();

	void calibrationPipeline();

};
