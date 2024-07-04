#pragma once
#include "CalibrationParametersDto.h"
#include "CalibrationData.h"
#include <string>

class ICalibrationViewListener {
public:

	/**
	 * @brief Computes the diameter of a MLA by taking the mean of both x and y spacing and converting it to um.
	 * 
	 * 
	 * @param calibData object from where dx and dy is drawn.
	 * @def CONVERSION_PX_microM: 5 um/px 
	 * @return MLA diameter in um.
	 */
	virtual float computeDiameter(CalibrationData calibData) = 0;
		/**
	 * @brief Validates if user selected parameters is within acceptable range.
	 * 
	 * @param param Calibration parameter object
	 * @return uint8_t value indicating invalid parameters or 0 if valid.
	 */
	virtual uint8_t validateParameters(CalibrationParametersDto param) = 0;
	/**
	 * @brief Set the default parameters for the calibration in the calibration engine.
	 * 
	 */
	virtual void OnDefaultParameters() = 0;
	/**
	 * @brief Set parameters on the calibration engine.
	 * 
	 * @param param Calibration parameter object
	 */
	virtual void SetCalibrationParameters(CalibrationParametersDto param) = 0;
	/**
	 * @brief Get the Calibration Parameters object
	 * 
	 * @return  CalibrationParametersDto: object containing the calibration parameters set on the engine.
	 */
	virtual CalibrationParametersDto GetCalibrationParameters() = 0;

	/**
	 * @brief Perform the calibration of the last calibration frame.
	 * 
	 * It ensures to get the latest frame, input it into the engine and recover the calibration data. Then, 
	 * it updates the controller's calibration data and update the view.
	 * 
	 * @return  CalibrationData: object containing the calibration data.
	 */
	virtual CalibrationData OnCalibrate() = 0;
	/**
	 * @brief Handles click on the Button "Show Error Heatmap".
	 * 
	 * It draws the error heatmap from the last calibration data and display it.
	 * 
	 */
	virtual void OnShowErrorHeatmap() = 0;
	/**
	 * @brief Get the circles detected in the last calibration frame.
	 * 
	 * @return std::vector<cv::Point2d> vector of points representing the circles detected.
	 */
	virtual std::vector<cv::Point2d> GetCircles() = 0;
	/**
	 * @brief Handles click on the Button "Close".
	 * 
	 */
	virtual void OnClose() = 0;

	/**
	 * @brief Save the calibration data to a file.
	 * 
	 * @param path Path to the file where the calibration data will be saved.
	 */
	virtual void SaveCalibrationData(std::string path) = 0;
	/**
	 * @brief Get the calibration data.
	 * 
	 * @return CalibrationData object containing the calibration data.
	 */
	virtual CalibrationData GetCalibrationData() = 0;

	/**
	 * @brief Store the calibration data pair.
	 * 
	 * Make a pair <CalibrationParametersDto, CalibrationData> and store it in a list.
	 */
	virtual void storeCalibrationDataPair() = 0;
	/**
	 * @brief Delete the calibration data list.
	 * 
	 */
	virtual void deleteCalibrationDataList() = 0;
	/**
	 * @brief Compute the global result of the calibration data list.
	 * 
	 * First, it searches for the calibrationData with the smallest error. 
	 * THe global result consists of the following data:
	 * - the circles center position of the calibration with the smallest error
	 * - the image of the calibration with the smallest error
	 * - the reference circle of the calibration with the smallest error
	 * - the average X and Y spacing through all the calibrations
	 * - recomputed error estimation based on the global data
	 * - heatmap of the global error
	 * @return CalibrationData object containing the global result.
	 */
	virtual CalibrationData computeGlobalResult() = 0;
	/**
	 * @brief Save the calibration data list to a file.
	 * 
	 * @param path Path to the file where the calibration data list will be saved.
	 */
	virtual void saveCalibrationDataListFile(std::string path) = 0;
};
