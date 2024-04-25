#include "CalibrationEngine.h"
#include "../event/EventDispatcher.h"
#include "../event/CalibrationStartEvent.h"


using namespace cv;
using namespace Eigen;

CalibrationEngine::CalibrationEngine() {
    this->gaussKernel = Size(15, 15);
    this->blockSize = 31;
    this->c = 3;
    this->clusterDistance = 20;
    this->useInvertImage = false;
    this->drawCircles = false;
    this->drawGrid = true;


    this->defaultParameters = CalibrationParametersDto(gaussKernel, blockSize, c, clusterDistance, useInvertImage, drawCircles, drawGrid);
}

void CalibrationEngine::setParameters(CalibrationParametersDto param) {
    this->gaussKernel = param.getGaussKernel();
	this->blockSize = param.getBlockSize();
	this->c = param.getC();
	this->clusterDistance = param.getClusterDistance();
    this->useInvertImage = param.getUseInvertImage();
	this->drawCircles = param.getDrawCircles();
	this->drawGrid = param.getDrawGrid();
}

CalibrationParametersDto CalibrationEngine::getParameters() {
    return CalibrationParametersDto(gaussKernel, blockSize, c, clusterDistance, useInvertImage, drawCircles, drawGrid);
}

void CalibrationEngine::setDefaultParameters() {
	this->gaussKernel = defaultParameters.getGaussKernel();
	this->blockSize = defaultParameters.getBlockSize();
	this->c = defaultParameters.getC();
	this->clusterDistance = defaultParameters.getClusterDistance();
    this->useInvertImage = defaultParameters.getUseInvertImage();
    this->drawCircles = defaultParameters.getDrawCircles();
    this->drawGrid = defaultParameters.getDrawGrid();
}

CalibrationParametersDto CalibrationEngine::getDefaultParameters() const {
	return defaultParameters;
}

Mat CalibrationEngine::generateThresholdImg(const Mat& img) {
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, gaussKernel, 0);
    Mat thresh;
    adaptiveThreshold(gray, thresh, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, c);
    return thresh;
}

std::vector<int> CalibrationEngine::intensityHist(const Mat& image) {
    std::vector<int> intensity;
    for (int i = 0; i < image.rows; ++i) {
        intensity.push_back(sum(image.row(i))[0] / 255);
    }
    return intensity;
}

std::vector<std::vector<int>> CalibrationEngine::clusterValues(const std::vector<int>& values) {
    std::vector<std::vector<int>> clusters;

    for (const auto& val : values) {
        bool foundCluster = false;
        for (auto& cluster : clusters) {
            if (!cluster.empty() && std::abs(val - cluster.front()) < clusterDistance) {
                cluster.push_back(val);
                foundCluster = true;
                break;
            }
        }
        if (!foundCluster) {
            clusters.push_back({ val });
        }
    }
    return clusters;
}


std::vector<double> CalibrationEngine::getPeaks(const std::vector<int>& intensityHist) {
    // Compute the first derivative as the difference between consecutive values
    std::vector<int> firstDerivative;
    for (size_t i = 0; i < intensityHist.size() - 1; ++i) {
        firstDerivative.push_back(static_cast<int>(intensityHist[i + 1] - intensityHist[i]));
    }

    // Find indexes of potential peaks by looking for sign changes in the first derivative
    std::vector<int> potentialPeaks;
    for (size_t i = 0; i < firstDerivative.size() - 1; ++i) {
        if (firstDerivative[i] >= 0 && firstDerivative[i + 1] <= 0) {
            potentialPeaks.push_back(i + 1);
        }
    }

    // Cluster neighboring values to get the average intensity of each peak
    std::vector<std::vector<int>> intensityClust = clusterValues(potentialPeaks);
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

std::vector<Point2d> CalibrationEngine::getCircles(const Mat& image) {
    std::vector<int> intensityY = intensityHist(image);
    std::vector<double> peaksY = getPeaks(intensityY);
    std::vector<int> intensityX = intensityHist(image.t());
    std::vector<double> peaksX = getPeaks(intensityX);

    std::vector<Point2d> circles;
    // Generate all possible circles and sorting them by y-coordinate
    for (double y : peaksY) {
        for (double x : peaksX) {
            circles.push_back(Point2d(x, y));
        }
    }
    return circles;
}

void CalibrationEngine::initializeMatrixA(int numCircles) {
    // Matrix A is a 2n x 4 matrix where n is the number of circles
    // It is a fixed matrix that determine the relationship between the circles and the grid
    // should one be computed once
    
    // verify is the matrix A is initialized for the given number of circles
    if (A.rows() == 2 * numCircles && A.cols() == 4) {
		return;
	}
    // if not initialize yet
    int nbX = static_cast<int>(std::sqrt(numCircles));  // Number of circles on the x-axis
    int nbY = numCircles / nbX;                         // Number of circles on the y-axis

    A.resize(2 * numCircles, 4);
    for (int i = 0; i < numCircles; ++i) {
        A(i, 0) = 1;
        A(i, 1) = 0;
        A(i, 2) = i % nbX;
        A(i, 3) = 0;
    }
    // Second half of the rows
    for (int i = numCircles; i < 2 * numCircles; ++i) {
        A(i, 0) = 0;
        A(i, 1) = 1;
        A(i, 2) = 0;
        A(i, 3) = (int)(i - numCircles) / nbX;
    }
    svd = Eigen::JacobiSVD<Eigen::MatrixXd>(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
}

CalibrationData* CalibrationEngine::applyCalibrationPipeline(const Mat& image){
    Mat workingImage = image.clone();
    if (useInvertImage) {
		bitwise_not(image, workingImage);
	}
    Mat thresh = generateThresholdImg(workingImage);
    std::vector<Point2d> circles = getCircles(thresh);

    int numCircles = circles.size();
    if (numCircles < 4) {
		return nullptr;
    }
    initializeMatrixA(numCircles);

    // Matrix B is a 2n x 1 matrix where n is the number of circles
    // It is a matrix that contains the coordinates of the circles
    // where the first n rows are the x-coordinates and the second n rows are the y-coordinates
    Eigen::MatrixXd B(2 * numCircles, 1);
    for (int i = 0; i < numCircles; ++i) {
        B(i, 0) = circles[i].x;
        B(i + numCircles, 0) = circles[i].y;
    }
    
    // Compute the least square solution of the system
    // X = (cx0, cy0, dx, dy)
    Eigen::MatrixXd X = svd.solve(B);

    // Error computation
    double error = (A * X - B).norm();

    // check if the solution is valid
    if (X(2) < 0.01 || X(3) < 0.01) {
        return nullptr;
    }
    /** 
    if (drawCircles) {
		double radius = (X(2) + X(3)) / 4;
        for (const auto& c : circles) {
			cv::circle(workingImage, c, radius, Scalar(0, 0, 255), 1);
		}
	}

    // draw circle centers
    for (const auto& c : circles) {
		cv::circle(workingImage, c, 1, Scalar(0, 0, 255), -1);
	}

    if (drawGrid) {
        // Add grid lines with spacing X(2) for X and X(3) for Y
        for (double i = -X(0); i < workingImage.cols; i += X(2)) {
            line(workingImage, Point(0, i), Point(workingImage.cols, i), Scalar(0, 0, 255), 1);
        }
        for (double i = -X(1); i < workingImage.rows; i += X(3)) {
            line(workingImage, Point(i, 0), Point(i, workingImage.rows), Scalar(0, 0, 255), 1);
        }
    }
    rectangle(workingImage, Point(0, 0), Point(215, 30), Scalar(0, 0, 0), -1);
    putText(workingImage, "Calibration Result Frame", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 1);
    */
    return new CalibrationData(workingImage, X(0), X(1), X(2), X(3), error, circles);
}

