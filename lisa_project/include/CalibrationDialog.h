#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "ICalibrationViewListener.h"
#include "PreviewPanel.h"
#include "PreviewController.h"
#include "CalibrationParametersDto.h"
#include "CalibrationData.h"

/**
 *	@class CalibrationDialog.
 * @brief Dialog for the calibration view.
 * @details This class is responsible for displaying the calibration view and handling the user input.
 **/
class CalibrationDialog : public wxDialog {
	wxWindow* parent;
	ICalibrationViewListener* listener;

	//=== Parameters ===//
	wxCheckBox* useInvertImage;
	wxSpinCtrl* gaussBlurSize;
	int m_gaussBlurSize;
	wxSpinCtrl* blockSize;
	int m_blockSize;
	wxSpinCtrl* c;
	wxSpinCtrl* clusterDistance;
	wxCheckBox* drawCircles;
	wxCheckBox* drawGrid;
	wxStaticText* calibCounter;

	//=== Results ===//
	wxStaticText* cx0_value;
	wxStaticText* cy0_value;
	wxStaticText* dx_value;
	wxStaticText* dy_value;
	wxStaticText* error_value;

	//=== Buttons ===//
	PreviewPanel* previewPanel;
	wxTextCtrl* apertureTextCtrl;
	wxButton* calibrateButton;
	wxButton* saveButton;
	wxButton* defaultParametersButton;
	wxButton* confirmButton;
	wxButton* restartButton;

	//== Debug buttons ==//
	wxButton* showErrorHeatmap;
	wxButton* showCirclesPos;

	/**
	 * @brief Updates values on the parameters view.
	 * 
	 * @param param object containing parameters values to be updated.
	 */
	void updateParametersView(CalibrationParametersDto param);
	/**
	 * @brief Updates values on the results view.
	 * 
	 * @param calibData object containing calibration data values to be updated.
	 */
	void updateResultsView(CalibrationData calibData);
	/**
	 * @brief Construct a CalibrationParameters object from parameters values on the view.
	 * 
	 * @return CalibrationParametersDto object containing the calibration parameters.
	 */
	CalibrationParametersDto getCalibrationParameters();
	/**
	 * @brief Validates if user selected parameters is within acceptable range.
	 * 
	 * @param param Calibration parameter object
	 * @return bool value indicating invalid parameters or 0 if valid.
	 */
	bool validateParameters(CalibrationParametersDto param);
	/**
	 * @brief Resets the UI to the default state.
	 * 
	 * Set engine to default parameters and reset the view.
	 * 
	 */
	void resetUI();
public:
	CalibrationDialog(wxWindow* parent, ICalibrationViewListener* controller, IPreviewListener* previewListener);

	/**
	 * @brief Displays the calibration dialog. First, it collects parameters data and updates
	 * its values on the view beforing showing it.
	 * 
	 */
	void ShowCalibrationDialog();
	/**
	 * @brief Get the Preview Panel object
	 * 
	 * @return PreviewPanel* object containing the preview panel.
	 */
	PreviewPanel* getPreviewPanel();

	/**
	 * @brief Implements custom behavior when the spin control is incremented. 
	 * 
	 *  Odd spins only get odd values. First, it detects the direction of increment and then sets the value to the next odd number.
	 * 
	 * @param event Spin event object.
	 */
	void OnOddSpin(wxSpinEvent& event);
	/**
	 * @brief Handles the event when the dialog is closed.
	 * 
	 */
	void OnClose(wxCloseEvent& event);
	/**
	 * @brief Performs the calibration.
	 * 
	 * Collects the parameters data, validates it, set it into the listener, ask listener to calibrate and updates the view accordingly.
	 * 
	 */
	void OnCalibrate(wxCommandEvent& event);
	/**
	 * @brief Set parameters default values.
	 * 
	 * Asks listener to set default parameters and updates the view.
	 * 
	 */
	void OnDefaultParameters(wxCommandEvent& event);
	/**
	 * @brief Save the calibration data to a file.
	 * 
	 * Opens a file dialog to select the file to save the calibration data and asks the listener to save it.
	 * 
	 */
	void OnSave(wxCommandEvent& event);
	/**
	 * @brief Opens the error heatmap.
	 * 
	 * Asks the listener to show the error heatmap.
	 * 
	 */
	void OnShowErrorHeatmap(wxCommandEvent& event);
	/**
	 * @brief Show circle centers position list.
	 * 
	 * Create a frame with a list of circle centers positions, data provided by the listener.
	 * 
	 */
	void OnShowCirclesPos(wxCommandEvent& event);
	/**
	 * @brief Manages calibration process
	 * 
	 * When the user clicks the confirm button, it tells the listener to store the data pair and increment the calibration counter.
	 * If the calibration counter is less than five, the UI is reset to the default state.
	 * If the calibration counter is equal to five, the listener is asked to compute the global results and the results dialog is displayed.
	 * For the next calibration, the whole calibration data list is save into a file and the calibration dialog is closed.
	 * 
	 */
	void OnConfirm(wxCommandEvent& event);
	/**
	 * @brief Displays the results dialog.
	 * 
	 * @param globalResult object containing the global calibration results.
	 */
	void displayResultsDialog(CalibrationData& globalResult);
	/**
	 * @brief Handles the event when the dialog is restarted.
	 * 
	 * Clean the calibration data list and reset the UI.
	 * 
	 */
	void OnRestart(wxCommandEvent& event);
};
