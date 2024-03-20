#include "CalibrationController.h"
#include "EventDispatcher.h"
#include "CalibrationStartEvent.h"


using namespace cv;
using namespace Eigen;

CalibrationController::CalibrationController() {
	this->gaussKernel = Size(15, 15);
	this->blockSize = 31;
	this->c = 3;
	this->clusterDistance = 10;

	EventDispatcher::Instance().SubscribeToEvent<CalibrationStartEvent>(
		[this](const CalibrationStartEvent& event) {
			HandleCalibrationStart();
		}
	);
}

void CalibrationController::HandleCalibrationStart()
{
	// Launch Calibration Preview in order to get a calibration frame
	// apply the calibration pipeline to the frame	
}

void CalibrationController::setParameters(const cv::Size& gaussKernel, int blockSize, double c, double clusterDistance) {
	this->gaussKernel = gaussKernel;
	this->blockSize = blockSize;
	this->c = c;
	this->clusterDistance = clusterDistance;
}

Mat CalibrationController::generateThresholdImg(const Mat& img) {
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, gaussKernel, 0);
    Mat thresh;
    adaptiveThreshold(gray, thresh, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, c);
    return thresh;
}

std::vector<int> CalibrationController::intensityHist(const Mat& image) {
    std::vector<int> intensity;
    for (int i = 0; i < image.rows; ++i) {
        intensity.push_back(sum(image.row(i))[0] / 255);
    }
    return intensity;
}

MatrixXd CalibrationController::pairwiseDistances(const MatrixXd& values) {
    int numPoints = values.rows();
    MatrixXd distances(numPoints, numPoints);
    for (int i = 0; i < numPoints; ++i) {
        for (int j = 0; j < numPoints; ++j) {
            distances(i, j) = (values.row(i) - values.row(j)).norm();
        }
    }
    return distances;
}

MatrixXd CalibrationController::generateAdjacencyMatrix(const MatrixXd& dist, double clusterDistance) {
    MatrixXd adjacencyMatrix = MatrixXd::Zero(dist.rows(), dist.cols());

    // Iterate over each element of dist
    for (int i = 0; i < dist.rows(); ++i) {
        for (int j = 0; j < dist.cols(); ++j) {
            // If distance is less than clusterDistance, set adjacency to 1
            double elem = dist(i, j);
            if (elem < clusterDistance) {
                adjacencyMatrix(i, j) = 1.0; // or any other value representing adjacency
            }
        }
    }
    return adjacencyMatrix;
}

std::vector<std::vector<double>> CalibrationController::clusterValues(const std::vector<double>& values) {
    MatrixXd dist = pairwiseDistances(Map<const MatrixXd>(&values[0], values.size(), 1));
    MatrixXd adjacencyMatrix = generateAdjacencyMatrix(dist, clusterDistance);

    std::vector<std::vector<double>> clusters;
    std::vector<bool> visited(values.size(), false); // Track visited values

    for (int i = 0; i < values.size(); ++i) {
        if (visited[i]) continue; // If value is already part of a cluster, skip it
        std::vector<double> cluster;
        cluster.push_back(values[i]); // Start a new cluster with this value
        visited[i] = true; // Mark it as visited

        for (int j = i + 1; j < values.size(); ++j) {
            if (!visited[j] && adjacencyMatrix(i, j) > 0) {
                cluster.push_back(values[j]); // Add adjacent values to the cluster
                visited[j] = true; // Mark them as visited
            }
        }

        clusters.push_back(cluster); // Add the cluster to the list of clusters
    }

    return clusters;
}


std::vector<double> CalibrationController::getPeaks(const std::vector<int>& intensityHist) {
    std::vector<double> firstDerivative;
    for (size_t i = 0; i < intensityHist.size() - 1; ++i) {
        firstDerivative.push_back(static_cast<double>(intensityHist[i + 1] - intensityHist[i]));
    }
    std::vector<double> potentialPeaks;
    for (size_t i = 0; i < firstDerivative.size() - 1; ++i) {
        if (firstDerivative[i] >= 0 && firstDerivative[i + 1] <= 0) {
            potentialPeaks.push_back(i + 1);
        }
    }
    std::vector<std::vector<double>> intensityClust = clusterValues(potentialPeaks);
    std::vector<double> peaks;
    for (const auto& cluster : intensityClust) {
        double sum = 0.0;
        for (double val : cluster) {
            sum += val;
        }
        peaks.push_back(sum / cluster.size());
    }
    return peaks;
}

std::vector<cv::Point2d> CalibrationController::getCircles(const Mat& image) {
    std::vector<int> intensityX = intensityHist(image);
    std::vector<double> peaksX = getPeaks(intensityX);
    std::vector<int> intensityY = intensityHist(image.t());
    std::vector<double> peaksY = getPeaks(intensityY);

    std::vector<cv::Point2d> circles;
    for (double x : peaksX) {
        for (double y : peaksY) {
            circles.push_back(Point2d(x, y));
        }
    }
    return circles;
}

void CalibrationController::initializeMatrixA(int numCircles) {
    // verify is the matrix A is initialized for the given number of circles
    if (A.rows() == 2 * numCircles && A.cols() == 4) {
		return;
	}
    int nbX = (numCircles + 1) / 2; // Assuming a rectangular grid
    int nbY = numCircles / nbX;
    A.resize(2 * numCircles, 4);
    A.block(0, 0, numCircles, 1).setConstant(1);
    A.block(0, 2, numCircles, 1) = Eigen::VectorXd::LinSpaced(nbX, 0, nbX - 1).replicate(1, nbY).transpose().col(0).head(numCircles);
    A.block(numCircles, 1, numCircles, 1).setConstant(1);
    A.block(numCircles, 3, numCircles, 1) = Eigen::VectorXd::LinSpaced(nbY, 0, nbY - 1).replicate(1, nbX).row(0).head(numCircles);
    svd = Eigen::JacobiSVD<Eigen::MatrixXd>(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
}

CalibrationData* CalibrationController::applyCalibrationPipeline(const cv::Mat& image){
    cv::Mat thresh = generateThresholdImg(image);
    std::vector<cv::Point2d> circles = getCircles(thresh);
    std::sort(circles.begin(), circles.end(), [](const cv::Point2d& a, const cv::Point2d& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
        });

    int numCircles = circles.size();
    initializeMatrixA(numCircles);
    Eigen::MatrixXd B(2 * numCircles, 1);
    for (int i = 0; i < numCircles; ++i) {
        B(i, 0) = circles[i].x;
        B(i + numCircles, 0) = circles[i].y;
    }

    Eigen::VectorXd sv = svd.singularValues();
    Eigen::MatrixXd U = svd.matrixU();
    Eigen::MatrixXd V = svd.matrixV();

    Eigen::VectorXd S_inv = sv.array().inverse();
    Eigen::VectorXd X = V * S_inv.asDiagonal() * U.transpose() * B;

    // Verify is X is not null
    if (X[2] == 0 || X[3] == 0) {
        return new CalibrationData();
	}

    cv::Mat outputImage = image.clone();
    for (double i = X[2]; i < 512; i += X[2]) {
        cv::line(outputImage, cv::Point(0, static_cast<int>(i)), cv::Point(image.cols - 1, static_cast<int>(i)), cv::Scalar(0, 0, 255), 1);
    }
    for (double j = X[3]; j < 512; j += X[3]) {
        cv::line(outputImage, cv::Point(static_cast<int>(j), 0), cv::Point(static_cast<int>(j), image.rows - 1), cv::Scalar(0, 0, 255), 1);
    }

    return new CalibrationData(outputImage, X[2], X[3], circles);
}

