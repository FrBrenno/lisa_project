#pragma once
#include "BaseController.h"
#include "ImageController.h"
#include "IPreviewListener.h"
#include "IPreview.h"
#include <wx/wx.h>
#include <wx/timer.h>

constexpr auto PREVIEW_IMAGE_RATE = 1000/24;

/**
 * @class PreviewController
 * @brief Controller class responsible to manage the preview of the image.
 * 
 */
class PreviewController :
    public wxEvtHandler, public BaseController, public IPreviewListener
{
    /**
     * @brief ImageController responsible to acquire image.
     * 
     */
    ImageController* imageController;
    /**
     * @brief PreviewHolder responsible of managing the image holder.
     * 
     */
    IPreview* previewHolder;

    /**
     * @brief Timer responsible to update the preview.
     * 
     */
    wxTimer* previewTimer;
    /**
     * @brief Indicates if the preview is on.
     * 
     */
    bool isPreviewOn;
    /**
     * @brief Indicates if the image has changed since last image acquisition.
     * 
     */
    bool hasImageChanged;

public:
    PreviewController(MyAppInterface* app, IApiService* wfsApiService, ImageController* imageController);
    ~PreviewController();

    /**
     * @brief Return if the preview is on.
     * 
     * @return true if the preview is on.
     */
    bool getIsPreviewOn() const;
    /**
     * @brief Return if the image has changed since last return of frame.
     * 
     * @return true if the image has changed.
     */
    bool getHasImageChanged() const;
    /**
     * @brief Return current frame.
     * 
     * @return wxImage the current frame.
     */
    wxImage getFrame();
    /**
     * @brief Set the frame in the preview.
     * 
     * @param image the frame to set.
     * @param notifyChange indicates if the frame change should be notified.
     */
    void setFrame(wxImage* image, bool notifyChange = true);

    /**
     * @brief Set the preview holder.
     * 
     * @param preview the preview holder.
     */
    void setPreview(IPreview* preview);

    /**
     * @brief Start the preview.
     * 
     */
    void startPreview() override;
    /**
     * @brief Stop the preview.
     * 
     */
    void stopPreview() override;
    /**
     * @brief Load the image in the preview.
     * 
     * @param image the image to load.
     */
    void onLoadImage(wxImage& image) override;
    /**
     * @brief Handles timer event.
     * 
     * It aquires a new frame from the API and update the current frame.
     * The timer ensures that the preview is updated at a fixed rate defined by the constant PREVIEW_IMAGE_RATE
     * 
     * @param event 
     */
    void onTimer(wxTimerEvent& event);

    // Inherited via IPreviewListener
    /**
     * @brief Handles preview button.
     * 
     */
    void onPreviewButton() override;
};

