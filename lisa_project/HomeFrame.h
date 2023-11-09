#pragma once
#include <wx/wx.h>
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
    /**
     * The name of the selected instrument.
     */
    std::string instrument_name;

    //=== GUI Elements ===//
    /**
     * This image control element that displays the camera image.
     */
    wxStaticBitmap* imageControl;

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
     * Sets the instrument name.
     * This instrument name will figure in the header and bottom of the software main window.
     * 
     * @param instrument_name Name of the selected instrument.
     */
    void setInstrumentName(std::string instrument_name);
    /**
     * Generate a Bitmap and display it on the image control.
     * @note This function is called by the ImageController that is the controller responsible to manage image acquisition.
     * 
     * @param newImage Reference to the new image to be displayed.
     */
    void updateImage(const wxImage& newImage);
};