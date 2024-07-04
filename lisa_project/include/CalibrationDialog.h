#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "ICalibrationViewListener.h"
#include "PreviewPanel.h"
#include "PreviewController.h"
#include "CalibrationParametersDto.h"
#include "CalibrationData.h"

/**
 **	@class CalibrationDialog.
 ** @brief Dialog for the calibration view.
 ** @details This class is responsible for displaying the calibration view and handling the user input.
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

	void ShowCalibrationDialog();
	PreviewPanel* getPreviewPanel();

	void OnOddSpin(wxSpinEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnCalibrate(wxCommandEvent& event);
	void OnDefaultParameters(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnShowErrorHeatmap(wxCommandEvent& event);
	void OnShowCirclesPos(wxCommandEvent& event);
	void OnConfirm(wxCommandEvent& event);
	void displayResultsDialog(CalibrationData& globalResult);
	void OnRestart(wxCommandEvent& event);
};
