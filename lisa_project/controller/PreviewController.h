#pragma once
#include "./controller/BaseController.h"
#include "./controller/ImageController.h"
#include "./interface/IPreviewHolderListener.h"
#include <wx/wx.h>
#include <wx/timer.h>

class PreviewController :
    public wxEvtHandler, public BaseController, public IPreviewHolderListener
{
    ImageController* imageController;

    wxStaticBitmap* imageControl;
    wxButton* previewButton;
    wxButton* captureButton;

    wxTimer* previewTimer;
    bool isPreviewOn;

public:
    PreviewController(MyAppInterface* app, WfsApiService* wfsApiService, ImageController* imageController);
    ~PreviewController();

    void setPreviewButton(wxButton* previewButton);
    void setImageControl(wxStaticBitmap* imageControl);

    void startPreview() override;
    void stopPreview() override;
    void updatePreviewButton();
    void updateImageFrame(wxImage* image);

    void onTimer(wxTimerEvent& event);
    void onPreviewButton();
};

