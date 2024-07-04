#pragma once
#include "BaseController.h"
#include "ICalibrationViewListener.h"
#include "CalibrationData.h"
#include "CalibrationParametersDto.h"
#include "PreviewController.h"
#include "CalibrationEngine.h"
#include "nlohmann/json.hpp"

/**
 **	@class CalibrationController.
 ** @brief Controller for the calibration view.
 ** @details This class is responsible for handling the calibration view and the calibration process.
 **/
class CalibrationController: public BaseController, public ICalibrationViewListener{
	/**
	 * @brief calibrationData: The last calibration data acquired.
	 * 
	 */
	CalibrationData* calibrationData;
	/**
	 * @brief previewController: The controller that manages the preview object 
	 * set in the calibration view.
	 * 
	 */
	PreviewController* previewController;
	/**
	 * @brief calibrationEngine: The engine that manages the calibration process.
	 * 
	 */
	CalibrationEngine* calibrationEngine;

	/**
	 * @brief lastCalibrationFrame: The last frame acquired for the calibration process.
	 * 
	 */
	wxImage* lastCalibrationFrame;
	/**	
	 * @brief calibrationDataList: The list of calibration data acquired during the calibration process.
	 * 
	 * @details This list is used to store the calibration data acquired during the calibration process
	 * alongside the calibration parameters used to acquire them.
	 */
	std::vector<std::pair<CalibrationParametersDto, CalibrationData>> calibrationDataList;

	/**
	 * @brief This private method draws in the image that is going to be displayed in the calibration 
	 * view.
	 * 
	 * @param calibData object contained the data neeeded to draw elements in the image.
	 * @return drawn image.
	 */
	wxImage drawOnImage(CalibrationData* calibData);
	/**
	 * @brief This private method updates the image displayed in the calibration view.
	 * 
	 * @param image The image to be displayed.
	 */
	void updateImage(cv::Mat image);
	/**
	 * @brief This private method constrcts a json object with the calibration data and parameters.
	 * 
	 * @param param calibration parameters
	 * @param calibData calibration data
	 * @param writeParam boolean indicating if the parameters should be written in the json object.
	 * @return json object with the calibration data and parameters, if writeParam is true.
	 */
	nlohmann::ordered_json constructCalibrationJson(CalibrationParametersDto param, CalibrationData calibData, bool writeParam);
public:
	CalibrationController(MyAppInterface* main, IApiService* wfsApiService, ImageController* imageController);
	~CalibrationController();


	// Event handlers

	/**
	 * @brief Handles the Start Calibration button event. It launches the calibration dialog and setup the preview.
	 * 
	 */
	void HandleCalibrationStart();

	// ICalibrationViewListener
	
	/**
	 * @brief Computes the diameter of a MLA by taking the mean of both x and y spacing and converting it to um.
	 * 
	 * 
	 * @param calibData object from where dx and dy is drawn.
	 * @def CONVERSION_PX_microM: 5 um/px 
	 * @return MLA diameter in um.
	 */
	float computeDiameter(CalibrationData calibData) override;
	/**
	 * @brief Validates if user selected parameters is within acceptable range.
	 * 
	 * @param param Calibration parameter object
	 * @return uint8_t value indicating invalid parameters or 0 if valid.
	 */
	uint8_t validateParameters(CalibrationParametersDto param) override;
	/**
	 * @brief Set the default parameters for the calibration in the calibration engine.
	 * 
	 */
	void OnDefaultParameters() override;
	/**
	 * @brief Set parameters on the calibration engine.
	 * 
	 * @param param Calibration parameter object
	 */
	void SetCalibrationParameters(CalibrationParametersDto param) override;
	/**
	 * @brief Get the Calibration Parameters object
	 * 
	 * @return  CalibrationParametersDto: object containing the calibration parameters set on the engine.
	 */
	CalibrationParametersDto GetCalibrationParameters() override;

	/**
	 * @brief Perform the calibration of the last calibration frame.
	 * 
	 * It ensures to get the latest frame, input it into the engine and recover the calibration data. Then, 
	 * it updates the controller's calibration data and update the view.
	 * 
	 * @return  CalibrationData: object containing the calibration data.
	 */
	CalibrationData OnCalibrate() override;
	/**
	 * @brief Handles click on the Button "Show Error Heatmap".
	 * 
	 * It draws the error heatmap from the last calibration data and display it.
	 * 
	 */
	void OnShowErrorHeatmap() override;
	/**
	 * @brief Get the circles detected in the last calibration frame.
	 * 
	 * @return  std::vector<cv::Point2d>: vector containing the circles detected.
	 */
	std::vector<cv::Point2d> GetCircles() override;
	/**
	 * @brief Handles the event of the calibration view being closed.
	 * 
	 */
	void OnClose() override;

	/**
	 * @brief Saves the calibration data to a file.
	 * 
	 * @param path Path to save the file.
	 */
	void SaveCalibrationData(std::string path) override;
	/**
	 * @brief Get the calibration data.
	 * 
	 * @return CalibrationData: object containing the calibration data.
	 */
	CalibrationData GetCalibrationData() override;

	/**
	 * @brief Store the calibration data pair.
	 * 
	 * Make a pair <CalibrationParametersDto, CalibrationData> and store it in a list.
	 */
	void storeCalibrationDataPair() override;
	/**
	 * @brief Delete the calibration data list.
	 * 
	 */
	void deleteCalibrationDataList() override;
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
	CalibrationData computeGlobalResult() override;
	/**
	 * @brief Save the calibration data list to a file.
	 * 
	 * @param path Path to save the file.
	 */
	void saveCalibrationDataListFile(std::string path) override;
};
