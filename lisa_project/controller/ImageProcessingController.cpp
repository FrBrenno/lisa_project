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
	// Display the threshold image
	cv::imshow("Threshold", thresh);
	// Convert to Eigen matrix
	Eigen::VectorXi eigen_image = cvMatToEigen(thresh);

	//=== Find circles ===//
	Eigen::VectorXi intensity_x = intensityHistogram(eigen_image, 0);
	Eigen::VectorXi intensity_y = intensityHistogram(eigen_image, 1);
	// display the histograms
	wxMessageBox("Histograms in x: " + std::to_string(intensity_x.size()) + "\nHistograms in y: " + std::to_string(intensity_y.size()), "Histograms", wxOK | wxICON_INFORMATION);
	
	// Find peaks in the intensity histograms
	Eigen::VectorXd peaks_x = findPeaks(intensity_x);
	Eigen::VectorXd peaks_y = findPeaks(intensity_y);
	// Display the peaks
	wxMessageBox("Peaks in x: " + std::to_string(peaks_x.size()) + "\nPeaks in y: " + std::to_string(peaks_y.size()), "Peaks", wxOK | wxICON_INFORMATION);

	// Construct circles
	std::vector<cv::Vec3f> circles;
	for (int i = 0; i < peaks_x.size(); ++i) {
		for (int j = 0; j < peaks_y.size(); ++j) {
			circles.push_back(cv::Vec3f(peaks_x[i], peaks_y[j], 1));
		}
	}

	// Draw circles & show the image
	for (int i = 0; i < circles.size(); ++i) {
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		cv::circle(*this->image, center, radius, cv::Scalar(0, 255, 0), 2);
	}
	cv::imshow("Calibration", *this->image);
	cv::waitKey(0);


}

Eigen::MatrixXi ImageProcessingController::cvMatToEigen(const cv::Mat& image)
{
	// Convert the image to Eigen matrix
	Eigen::MatrixXi result(image.rows, image.cols);
	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j) {
			result(i, j) = static_cast<int>(image.at<uchar>(i, j));
		}
	}

	return result;
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

Eigen::VectorXi ImageProcessingController::intensityHistogram(const Eigen::MatrixXi& image, int axis)
{
	// Transpose the image if 'axis' is set to 1
	Eigen::MatrixXi img = (axis == 0) ? image : image.transpose();

	// Calculate the row-wise sum of pixel values, considering 255 as the maximum intensity
	Eigen::VectorXi intensity(img.rows());
	for (int i = 0; i < img.rows(); ++i) {
		intensity[i] = static_cast<int>(img.row(i).sum() / 255); // integer division
	}

	// Return the calculated intensity histogram
	return intensity;
}

Eigen::VectorXd ImageProcessingController::findPeaks(const Eigen::VectorXi& intensity)
{
	// Compute the first derivative of the intensity histogram
	Eigen::VectorXi diff = intensity.tail(intensity.size() - 1) - intensity.head(intensity.size() - 1);

	// Find the indexes of the peaks
	std::vector<int> peaks_indexes;
	for (int i = 0; i < diff.size() - 1; ++i) {
		if (diff[i] > 0 && diff[i + 1] < 0) {
			peaks_indexes.push_back(i);
		}
	}

	// Extract the peak values
	Eigen::VectorXi peaks(peaks_indexes.size());
	for (int i = 0; i < peaks_indexes.size(); ++i) {
		peaks[i] = static_cast<int>(intensity[peaks_indexes[i]]);
	}

	// Cluster close peaks
	std::vector<Eigen::VectorXi> peaks_clust = this->clusterValues(peaks);

	// Compute the mean intensity of the clustered peaks
	Eigen::VectorXd mean_peaks(peaks_clust.size());
	for (int i = 0; i < peaks_clust.size(); ++i) {
		mean_peaks[i] = peaks_clust[i].mean();
	}

	return mean_peaks;

}	
std::vector<Eigen::VectorXi> ImageProcessingController::clusterValues(Eigen::VectorXi values) {
	int num_points = values.rows();

	Eigen::MatrixXi distances = this->pairwiseDistance(values);

	Eigen::MatrixXi adjacency_matrix(distances.rows(), distances.cols());
	for (int i = 0; i < distances.rows(); ++i) {
		for (int j = 0; j < distances.cols(); ++j) {
			adjacency_matrix(i, j) = (distances(i, j) < this->clustering_distance) ? 1 : 0;
		}
	}

	std::vector<std::vector<int>> clusters;

	for (int i = 0; i < num_points; ++i) {
		bool found_cluster = false;

		for (auto& cluster : clusters) {
			for (int c : cluster) {
				if (adjacency_matrix(i, c)) {
					cluster.push_back(i);
					found_cluster = true;
					break;
				}
			}
			if (found_cluster) {
				break;
			}
		}

		if (!found_cluster) {
			clusters.push_back({ i });
		}
	}

	std::vector<Eigen::VectorXi> clustered_values;
	for (auto& cluster : clusters) {
		Eigen::VectorXi cluster_values(cluster.size());
		for (int i = 0; i < cluster.size(); ++i) {
			cluster_values[i] = values(cluster[i]);
		}
		clustered_values.push_back(cluster_values);
	}

	return clustered_values;
}


Eigen::MatrixXi ImageProcessingController::pairwiseDistance(Eigen::VectorXi values) {
	int num_points = values.rows();
	Eigen::MatrixXi distances(num_points, num_points);

	for (int i = 0; i < num_points; ++i) {
			for (int j = 0; j < num_points; ++j) {
				distances(i, j) = static_cast<int>(std::sqrt(std::pow(values[i] - values[j], 2)));
			}
		}

	return distances;
}
