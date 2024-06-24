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
     * Controllers that listen to this view.
     */
    IHomeFrameListener* listener;

    //=== GUI Elements ===//
    PreviewPanel* previewPanel;
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

    void OnCalibrationStart(wxCommandEvent& event);

	void OnWfsManual(wxCommandEvent& event);
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

    /**
    * Adds a listener to the list of listeners.
    ** 
    ** @param listener Listener to be added.
    **/
    void setListener(IHomeFrameListener* listener);

    void setPreviewListener(IPreviewListener* listener);
    PreviewPanel* getPreviewPanel();
};