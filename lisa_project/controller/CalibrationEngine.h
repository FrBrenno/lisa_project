#include "lib/Eigen/Dense"
#include "BaseController.h"
#include "model/CalibrationData.h"
#include "model/Dto/CalibrationParametersDto.h"
#include <opencv2/opencv.hpp>
#include <vector>

class CalibrationEngine{
    bool useInvertImage;
    bool drawCircles;
    bool drawGrid;

    cv::Size gaussKernel;
    int blockSize;
    double c;
    double clusterDistance;

    CalibrationParametersDto defaultParameters;

    Eigen::MatrixXd A;
    Eigen::JacobiSVD<Eigen::MatrixXd> svd;

    void initializeMatrixA(int numCircles);

    cv::Mat generateThresholdImg(const cv::Mat& img);
    std::vector<int> intensityHist(const cv::Mat& image);
    std::vector<std::vector<int>> clusterValues(const std::vector<int>& values);
    std::vector<double> getPeaks(const std::vector<int>& intensityHist);
    std::vector<cv::Point2d> getCircles(const cv::Mat& image);
public:
    CalibrationEngine();

    void setParameters(CalibrationParametersDto param);
    CalibrationParametersDto getParameters();
    void setDefaultParameters();
    CalibrationParametersDto getDefaultParameters() const;

    CalibrationData* applyCalibrationPipeline(const cv::Mat& image);
};
