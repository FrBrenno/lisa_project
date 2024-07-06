#pragma once
#include <wx/wx.h>
#include <string>
#include "IHomeFrameListener.h"
#include "PreviewPanel.h"
#include "IPreviewListener.h"

/**
 * @class HomeFrame.
 * @brief This view is responsible to display the main windows of the software.
 * @details It is manage by its respective controller, HomeFrameController.
 */
class HomeFrame : public wxFrame
{
    /**
     * @brief Controllers that listen to this view.
     */
    IHomeFrameListener* listener;

    //=== GUI Elements ===//
    /**
     * @brief Panel used to display the preview image.
     */
    PreviewPanel* previewPanel;
    /**
     * @brief Name of the instrument in use.
     */
    std::string instrumentName;
    /**
     * Handles the event: OnInstrumentSelection, where the user can select a instrument within a list on a dialog box.
     * 
     * Dispatches InstrumentSelectionEvent.
     */
    void OnInstrumentSelection(wxCommandEvent& event);
    /**
     * @brief Loads an image from a file to preview.
     * 
     * Interacts with previewPanel to load image.
     */
    void OnLoadImage(wxCommandEvent& event);
    /**
     * @brief Handles the event: OnConnectAPI, where the user can connect to the Thorlabs WaveFront Sensor API.
     * 
     * Interacts with listener to connect to the API.
     */
    void OnConnectAPI(wxCommandEvent& event);
    /**
     * @brief Handles the event: OnCapture, where the user can capture an image from the plenoptic camera.
     * 
     * Interacts with previewPanel to capture image.
     */
    void OnCapture(wxCommandEvent& event);
    /**
     * @brief  Handles when the user clicks on the exit menu item or closes the window.
     * 
     * Dispatches ExitEvent.
     */
    void OnExit(wxCommandEvent& event);
    /**
     * @brief Handles the event: OnCalibrationStart, where the user can start the calibration process.
     * 
     * Stops the preview and disptaches CalibrationStartEvent.
     */
    void OnCalibrationStart(wxCommandEvent& event);
    /**
     * @brief Handles the event: OnWfsManual, where the user can open the Thorlabs WaveFront Sensor API manual.
     * 
     * Opens the manual in the default system viewer.
     */
	void OnWfsManual(wxCommandEvent& event);
    /**
     * @brief Handles when the user clicks on the about menu item.
     * 
     */
    void OnAbout(wxCommandEvent& event);

public:
    HomeFrame();

    /**
     * @brief Sets the instrument in use name.
     * 
     * The instrument name is displayed in the status text.
     * 
     * @param instrumentName Instrument in use.
     */
    void setInstrumentName(std::string instrumentName);

    /**
    * @brief Sets a listener to this view.
    * 
    * @param listener Listener to be set.
    **/
    void setListener(IHomeFrameListener* listener);
    /**
     * @brief Sets a listener to the preview panel.
     * 
     * @param listener Listener to be set.
     */
    void setPreviewListener(IPreviewListener* listener);
    /**
     * @brief Returns the preview panel.
     * 
     * @return PreviewPanel* pointer to the preview panel.
     */
    PreviewPanel* getPreviewPanel();
};