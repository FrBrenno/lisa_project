#include "PreviewController.h"

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
	this->previewTimer->Start(PREVIEW_IMAGE_RATE);
	this->isPreviewOn = true;
	this->previewHolder->updatePreviewButton(this->isPreviewOn);
}

void PreviewController::stopPreview()
{
	this->previewTimer->Stop();
	this->isPreviewOn = false;
	this->previewHolder->updatePreviewButton(this->isPreviewOn);
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

void PreviewController::setPreview(IPreview* preview)
{
	this->previewHolder = preview;
}
