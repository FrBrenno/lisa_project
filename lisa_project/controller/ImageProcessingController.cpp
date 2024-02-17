#include "ImageProcessingController.h"

ImageProcessingController::ImageProcessingController(MyAppInterface* main, WfsApiService* wfsApiService) : BaseController(main, wfsApiService)
{}

unsigned char* ImageProcessingController::processImage(unsigned char* image_buffer, int rows, int cols)
{
	// create cv::Mat from image_buffer
	cv::Mat image(rows, cols, CV_8UC1, image_buffer);

    // Compute mean intensity of the grayscale image
    double meanIntensity = cv::mean(image)[0];

    // Set Canny thresholds based on mean intensity
    int lowThreshold = static_cast<int>(0.16 * meanIntensity);
    int highThreshold = static_cast<int>(0.20 * meanIntensity);

    // Apply Gaussian blur to reduce noise and enhance edges
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(3, 3), 0);

    // Perform edge detection using Canny
    cv::Mat edges;
    cv::Canny(blurredImage, edges, lowThreshold, highThreshold);

    // Use Hough Line Transform to detect lines
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

    // Define the threshold angle for considering a line as vertical or horizontal
    double verticalAngleThreshold = CV_PI / 2;  // 90 degrees
    double horizontalAngleThreshold = 0;         // 0 degrees

    // Define the acceptable range around the vertical axis
    double angleTolerance = CV_PI / 18;  // 10 degrees

    // Draw detected only vertical lines on the image
    for (const auto& line : lines) {
        float rho = line[0];
        float theta = line[1];
 
        if (std::abs(theta - verticalAngleThreshold) < angleTolerance ||
            std::abs(theta - horizontalAngleThreshold) < angleTolerance) 
        {
            cv::Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a * rho, y0 = b * rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000 * (a));
            pt2.x = cvRound(x0 - 1000 * (-b));
            pt2.y = cvRound(y0 - 1000 * (a));
            cv::line(image, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
        }
    }

    return image.data;
}
