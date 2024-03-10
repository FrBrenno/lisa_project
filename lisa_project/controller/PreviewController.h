#pragma once
#include "./controller/BaseController.h"
#include "./controller/ImageController.h"
#include <wx/wx.h>
#include <wx/timer.h>

class PreviewController :
    public wxEvtHandler, public BaseController
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

    void startPreview();
    void stopPreview();
    void updatePreviewButton();
    void updateImageFrame(wxImage* image);

    void onTimer(wxTimerEvent& event);
    void onPreviewButton();
};

