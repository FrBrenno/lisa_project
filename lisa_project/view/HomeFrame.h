#pragma once
#include <wx/wx.h>
#include <string>
#include "../interface/IHomeFrameListener.h"
#include "../interface/IPreviewHolder.h"
#include "../interface/IPreviewHolderListener.h"

/**
 * @class HomeFrame.
 * @brief This view is responsible to display the main windows of the software.
 * @details It is manage by its respective controller, HomeFrameController.
 */
class HomeFrame : public wxFrame, public IPreviewHolder
{
    /**
     * Controllers that listen to this view.
     */
    IHomeFrameListener* listener;
    IPreviewHolderListener* previewListener;

    //=== GUI Elements ===//
    /**
     * This image control element that displays the camera image.
     */
    wxStaticBitmap* imageControl;

    wxButton* captureButton;
    wxButton* previewButton;
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

public:
    HomeFrame();

    /**
     * Sets the instrument in use name.
     * 
     * @param instrumentName Instrument in use.
     */
    void setInstrumentName(std::string instrumentName);

    void setImage(wxImage* image);

    void resizeImage(wxImage* image);

    /**
    * Adds a listener to the list of listeners.
    ** 
    ** @param listener Listener to be added.
    **/
    void setListener(IHomeFrameListener* listener);

    wxStaticBitmap* getPreviewImageControl() override;
    wxButton* getPreviewButton() override;

    void setPreviewListener(IPreviewHolderListener* listener) override;
};