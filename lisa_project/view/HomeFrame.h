#pragma once
#include <wx/wx.h>
#include <string>
#include "../controller/HomeFrameController.h"

/**
 * @class HomeFrame.
 * @brief This view is responsible to display the main windows of the software.
 * @details It is manage by its respective controller, HomeFrameController.
 */
class HomeFrame : public wxFrame
{
    /**
     * View Controller that manages it.
     */
    HomeFrameController* controller;

    std::vector<BaseController*> listeners;
    //=== GUI Elements ===//
    /**
     * This image control element that displays the camera image.
     */
    wxBitmapButton* imageControl;

    wxButton* captureButton;
    wxButton* previewButton;
    wxTimer* previewTimer;
    bool isPreviewOn;
    /**
     * Name of the instrument in use.
     */
    std::string instrumentName;
    /**
     * Handles the event: OnInstrumentSelection, where the user can select a instrument within a list on a dialog box.
     * 
     * @param event OnInstrumentSelection event.
     */
    void OnInstrumentSelection(wxCommandEvent& event);

    void OnLoadImage(wxCommandEvent& event);

    void OnConnectAPI(wxCommandEvent& event);

    void OnCameraSettings(wxCommandEvent& event);

    void OnCapture(wxCommandEvent& event);
    /**
     * Handles when the user clicks on the exit menu item or closes the window.
     * 
     * @param event Exit event.
     */
    void OnExit(wxCommandEvent& event);
    /**
     * Handles when the user clicks on the about menu item.
     * 
     * @param event About event.
     */
    void OnAbout(wxCommandEvent& event);

    void updatePreviewButton();
    void stopPreview();
    void startPreview();
    void OnPreviewButton(wxCommandEvent& event);
public:
    HomeFrame(HomeFrameController* controller);

    /**
     * Sets the instrument in use name.
     * 
     * @param instrumentName Instrument in use.
     */
    void setInstrumentName(std::string instrumentName);

    /**
     * Generate a Bitmap and display it on the image control.
     * @note This function is called by the ImageController that is the controller responsible to manage image acquisition.
     * 
     * @param newImage Reference to the new image to be displayed.
     */
    void updateImage(wxTimerEvent& event);

    void setImage(wxImage* image);

    void resizeImage(wxImage* image);
    /**
    * Adds a listener to the list of listeners.
    ** 
    ** @param listener Listener to be added.
    **/
    void addListener(BaseController* listener);
};