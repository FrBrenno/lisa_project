#pragma once
#include "../controller/BaseController.h"
#include "../MyAppInterface.h"
#include <opencv2/opencv.hpp>
#include "lib/Eigen/Dense"


class ImageProcessingController: public BaseController
{
	cv::Mat* image;
	int rows, cols;

	int gauss_kernel_size;		// determines the size of the kernel
	int block_size;				// determines the size of the neighbourhood area
	int c;						//is a constant that is subtracted from the mean or weighted sum of the neighbourhood pixels.
	int clustering_distance;	// determines the distance threshold for the clustering algorithm

	Eigen::MatrixXi cvMatToEigen(const cv::Mat& image);
	
	cv::Mat generateThresholdImage();

	Eigen::VectorXi intensityHistogram(const Eigen::MatrixXi& image, int axis);
	Eigen::VectorXd findPeaks(const Eigen::VectorXi& intensity);
	std::vector<Eigen::VectorXi> clusterValues(Eigen::VectorXi values);
	Eigen::MatrixXi pairwiseDistance(Eigen::VectorXi values);
public:
	ImageProcessingController(MyAppInterface* main, IApiService* wfsApiService);

	void setImage(cv::Mat* image, int rows, int cols);
	cv::Mat getProcessedImage();

	void calibrationPipeline();

};
