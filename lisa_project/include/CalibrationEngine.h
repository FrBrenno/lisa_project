#include "Eigen/Dense"
#include "BaseController.h"
#include "CalibrationData.h"
#include "CalibrationParametersDto.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

/**
 * @brief Class used to solve the calibration problem.
 * 
 * This class is used to solve the calibration problem using the method described on the project report.
 * It uses the SVD method to solve the linear system and find the solution matrix.
 * 
 */
class CalibrationEngine{
    //**Parameters**//

    std::string aperture;
    bool useInvertImage;
    bool drawCircles;
    bool drawGrid;

    cv::Size gaussKernel;
    int blockSize;
    double c;
    double clusterDistance;

    /**
     * @brief CalibrationParametersDto object containing default parameters.
     * 
     */
    CalibrationParametersDto defaultParameters;

    /**
     * @brief Matrix A used to solve the calibration problem.
     * 
     */
    Eigen::MatrixXd A;
    /**
     * @brief Singular Value Decomposition object.
     * 
     */
    Eigen::JacobiSVD<Eigen::MatrixXd> svd;

    //**Methods**//
    /**
     * @brief Construct the matrix A used to solve the calibration problem as defined on the project report.
     * 
     * @param numCircles number of circles to be used on the calibration.
     */
    void initializeMatrixA(int numCircles);

    /**
     * @brief Generate the threshold image used on the calibration pipeline.
     * 
     * First, convert image to grayscale then apply a Gaussian blur and adaptive threshold.
     * It uses parameters gaussKernel, blockSize and c defined in as class attributes.
     * 
     * @param img input image.
     * @return thresholded image
     */
    cv::Mat generateThresholdImg(const cv::Mat& img);
    /**
     * @brief Compute the intensity histogram of an image.
     * 
     * Intensity histogram is the number of white pixels on each row of the image.
     * 
     * @param workingImage pre-processed input image
     * @return  vector containing the number of white pixels on each row of the image.
     */
    std::vector<int> intensityHist(const cv::Mat& workingImage);
    /**
     * @brief Cluster the intensity histogram values.
     * 
     * This method clusters the intensity histogram values into groups of similar values. The similarity
     * is defined by the clusterDistance parameter.
     * 
     * @param values intensity histogram values.
     * @return vector containing the clustered values.
     */
    std::vector<std::vector<int>> clusterValues(const std::vector<int>& values);
    /**
     * @brief Get the peaks of the intensity histogram.
     * 
     * This method finds the peaks of the intensity histogram by computing the first derivative of the intensity histogram vector.
     * Then, it clusters values of the first derivative to find the peaks using clusterValues method. Finally, it computes the average
     * of clustered values to defined a single peaks value.
     * 
     * @param intensityHist intensity histogram values.
     * @return vector containing the peaks of the intensity histogram.
     */
    std::vector<double> getPeaks(const std::vector<int>& intensityHist);
    /**
     * @brief Get the circles positions on the image.
     * 
     * This method finds the circles positions on the image by computing the peaks of the intensity histogram on the x and y axis.
     * Then, it generates all possible circles positions by combining the peaks of the x and y axis.
     * 
     * @param workingImage working image.
     * @return vector containing the circles positions.
     */
    std::vector<cv::Point2d> getCircles(const cv::Mat& workingImage);
public:
    CalibrationEngine();

    /**
     * @brief Set the Parameters values attributss given a CalibrationParametersDto object.
     * 
     * @param param CalibrationParametersDto object containing the parameters values.
     */
    void setParameters(CalibrationParametersDto param);
    /**
     * @brief Return the Parameters values attributes as a CalibrationParametersDto object.
     * 
     * @return  
     */
    CalibrationParametersDto getParameters();
    /**
     * @brief Set the default parameters values attributes using the defaultParameters attribute.
     * 
     */
    void setDefaultParameters();
    /**
     * @brief Return the default parameters values attributes as a CalibrationParametersDto object.
     * 
     * @return 
     */
    CalibrationParametersDto getDefaultParameters() const;

    /**
     * @brief Compute the mean error between the solution matrix and the actual found circle position matrix.
     * 
     * It computes the error vector which is the difference between the solution matrix and the actual found circle position vector.
     * Re-structure the error vector to ((errorX1, errorY1), (errorX2, errorY2), ... , (errorXn, errorYn)) and compute the each error and the norm of the error.
     * then it returns the average error through all local error vector and the error vector.
     * 
     * @param solMatrix Solution matrix given by SVD resolution of the linear system.
     * @param circleMatrix Circle position matrix found on the image.
     * @return  
     */
    std::pair<double, std::vector<double>> computeMeanError(const Eigen::MatrixXd& solMatrix, const Eigen::MatrixXd& circleMatrix);
    /**
     * @brief Compute a heatmap based in the error vector.
     * 
     * It normalizes the vector between 0 and 1 and then creates a heatmap image based on the error vector.
     * Blue for low error values and red for high error values.
     * Color coding : (255*(1-error), 0, 255*error)
     * 
     * @param circles circle positions list
     * @param errorVector error vector
     * @param thresh thresholded image
     * @param X solution matrix
     * @return Heatmap image
     */
    cv::Mat generateErrorHeatmap(const std::vector<cv::Point2d>& circles, const std::vector<double>& errorVector, const cv::Mat& thresh, const Eigen::MatrixXd& X);
    /**
     * @brief Apply the calibration pipeline to an image.
     * 
     * This method applies the calibration pipeline to an image. 
     * It first generates the threshold image using the generateThresholdImg method.
     * Then, it finds the circles positions on the image using the getCircles method. 
     * Finally, it solves the calibration problem using the
     * solution matrix and the error vector.
     * 
     * @param image input image
     * @return CalibrationData object containing the solution matrix, the error vector, the circles positions and the heatmap image.
     */
    CalibrationData* applyCalibrationPipeline(const cv::Mat& image);
};
