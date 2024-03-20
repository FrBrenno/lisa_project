#include "lib/Eigen/Dense"
#include "BaseController.h"
#include "CalibrationData.h"
#include <opencv2/opencv.hpp>
#include <vector>

class CalibrationController{
    cv::Size gaussKernel;
    int blockSize;
    double c;
    double clusterDistance;

    Eigen::MatrixXd A;
    Eigen::JacobiSVD<Eigen::MatrixXd> svd;

    void initializeMatrixA(int numCircles);

    cv::Mat generateThresholdImg(const cv::Mat& img);
    std::vector<int> intensityHist(const cv::Mat& image);
    Eigen::MatrixXd pairwiseDistances(const Eigen::MatrixXd& values);
    Eigen::MatrixXd generateAdjacencyMatrix(const Eigen::MatrixXd& dist, double clusterDistance);
    std::vector<std::vector<double>> clusterValues(const std::vector<double>& values);
    std::vector<double> getPeaks(const std::vector<int>& intensityHist);
    std::vector<cv::Point2d> getCircles(const cv::Mat& image);
public:
    CalibrationController();

    void setParameters(const cv::Size& gaussKernel, int blockSize, double c, double clusterDistance);

    CalibrationData* applyCalibrationPipeline(const cv::Mat& image);

    void HandleCalibrationStart();
};
