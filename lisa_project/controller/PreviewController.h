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
    PreviewController(MyAppInterface* app, IApiService* wfsApiService, ImageController* imageController);
    ~PreviewController();

    void setPreviewButton(wxButton* previewButton);
    void setCaptureButton(wxButton* captureButton);
    void setImageControl(wxStaticBitmap* imageControl);

    void startPreview() override;
    void stopPreview() override;
    void onCapture(wxWindow* window, wxBitmap bitmap) override;

    void updatePreviewButton();
    void updateImageFrame(wxImage* image);

    void onTimer(wxTimerEvent& event);
    void onPreviewButton();

    void setPreviewHolder(IPreviewHolder* previewHolder);
};

