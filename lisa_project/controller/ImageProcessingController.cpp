#include "ImageProcessingController.h"

ImageProcessingController::ImageProcessingController(MyAppInterface* main, bool is_wfs_connected) : BaseController(main, is_wfs_connected)
{}

unsigned char* ImageProcessingController::processImage(unsigned char* image_buffer, int rows, int cols)
{
	// create cv::Mat from image_buffer
	cv::Mat image(rows, cols, CV_8UC1, image_buffer);
	edgeDetection(image);
    return image.data;
}

void ImageProcessingController::edgeDetection(cv::Mat image)
{
    // Convert image to grayscale if it's not already
    if (image.channels() > 1) {
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    }

    // Perform edge detection using Canny
    cv::Mat edges;
    cv::Canny(image, edges, 100, 200);

    // Use Hough Line Transform to detect lines
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

    // Draw detected lines on the image
    for (const auto& line : lines) {
        float rho = line[0];
        float theta = line[1];
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
