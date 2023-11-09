#pragma once
#include <wx/wx.h>
#include <string>
#include "HomeFrameController.h"

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
    HomeFrameController* listener;

    //=== GUI Elements ===//
    /**
     * This image control element that displays the camera image.
     */
    wxStaticBitmap* imageControl;
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

    //TODO: Add methods to all available menu items
public:
    HomeFrame();

    /**
     * Sets the view listener, aka Controller.
     * 
     * @param controller HomeFrameController that manages this view.
     */
    void setListener(HomeFrameController* controller);

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
    void updateImage(const wxImage& newImage);
};