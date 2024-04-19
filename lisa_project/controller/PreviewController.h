#pragma once
#include "./controller/BaseController.h"
#include "./controller/ImageController.h"
#include "./interface/IPreviewListener.h"
#include "./interface/IPreview.h"
#include <wx/wx.h>
#include <wx/timer.h>

class PreviewController :
    public wxEvtHandler, public BaseController, public IPreviewListener
{
    ImageController* imageController;
    IPreview* previewHolder;

    wxTimer* previewTimer;
    bool isPreviewOn;

public:
    PreviewController(MyAppInterface* app, IApiService* wfsApiService, ImageController* imageController);
    ~PreviewController();

    bool getIsPreviewOn() const;
    wxImage* getFrame();
    void setFrame(wxImage* image);

    void setPreview(IPreview* preview);

    void startPreview();
    void stopPreview() override;
    void onLoadImage() override;

    void onTimer(wxTimerEvent& event);

    // Hérité via IPreviewListener
    void onPreviewButton() override;
};

