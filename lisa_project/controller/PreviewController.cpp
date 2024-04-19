#include "PreviewController.h"
#include "event/EventDispatcher.h"
#include "event/OnLoadImageEvent.h"

constexpr auto PREVIEW_IMAGE_RATE = 1000/24;

PreviewController::PreviewController(MyAppInterface* app, IApiService* wfsApiService, ImageController* imageController) :
	BaseController(app, wfsApiService)
{
	this->imageController = imageController;
	this->previewTimer = new wxTimer(this);
	this->Bind(wxEVT_TIMER, [this](wxTimerEvent& event) {
		this->onTimer(event);
	});
	this->isPreviewOn = false;
}

PreviewController::~PreviewController()
{
	this->previewTimer->Stop();
	delete this->previewTimer;
}

void PreviewController::startPreview()
{
    if (!this->isPreviewOn)
    {
        this->previewTimer->Start(PREVIEW_IMAGE_RATE);
        this->isPreviewOn = true;
        this->previewHolder->updatePreviewButton(this->isPreviewOn);
    }
}

void PreviewController::stopPreview()
{
    if (this->isPreviewOn)
    {
        this->previewTimer->Stop();
        this->isPreviewOn = false;
        this->previewHolder->updatePreviewButton(this->isPreviewOn);
	}
}

void PreviewController::onTimer(wxTimerEvent& event)
{
    if (this->wfsApiService->isApiConnectionActive())
    {
        if (this->isPreviewOn)
        {
            this->previewHolder->freezePreview();
            this->imageController->acquireImage();
            wxImage* image = this->imageController->getImage();
            if (image == nullptr)
            {
                this->stopPreview();
                return;
            }
            // Set the new image in the preview panel
            this->previewHolder->setImage(image);
            this->previewHolder->thawPreview();
            // Delete the old image to prevent memory leak
            delete image;
        }
    }
    else
    {
        this->stopPreview();
        wxMessageBox("WFS API connection is not active.", "Error", wxOK | wxICON_ERROR);
    }
}

void PreviewController::onPreviewButton()
{
	this->isPreviewOn ? this->stopPreview() : this->startPreview();
}

void PreviewController::onLoadImage()
{
    EventDispatcher::Instance().PublishEvent(
        OnLoadImageEvent()
    );
}

wxImage* PreviewController::getFrame()
{
    return this->previewHolder->getFrame();
}

void PreviewController::setPreview(IPreview* preview)
{
	this->previewHolder = preview;
}

void PreviewController::setFrame(wxImage* image)
{
	this->previewHolder->setImage(image);
}

bool PreviewController::getIsPreviewOn() const 
{
	return this->isPreviewOn;
}

