#include "PreviewController.h"

constexpr auto PREVIEW_IMAGE_RATE = 1000/24;

PreviewController::PreviewController(MyAppInterface* app, WfsApiService* wfsApiService, ImageController* imageController) : BaseController(app, wfsApiService)
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
	this->updatePreviewButton();
}

void PreviewController::stopPreview()
{
	this->previewTimer->Stop();
	this->isPreviewOn = false;
	this->updatePreviewButton();
}

void PreviewController::updatePreviewButton()
{
	if (this->isPreviewOn)
		this->previewButton->SetLabel("Stop Preview");
	else
		this->previewButton->SetLabel("Start Preview");
}

void PreviewController::updateImageFrame(wxImage* image)
{
	this->imageControl->SetBitmap(wxNullBitmap);
	wxBitmap* bitmap = new wxBitmap(*image);
	imageControl->SetBitmap(*bitmap);
	imageControl->Refresh();
}

void PreviewController::onTimer(wxTimerEvent& event)
{
	this->imageControl->Freeze();

	this->imageController->acquireImage();
	wxImage* image = this->imageController->getImage();

	this->updateImageFrame(image);
	this->imageControl->Thaw();
}

void PreviewController::onPreviewButton()
{
	this->isPreviewOn ? this->stopPreview() : this->startPreview();
}

void PreviewController::setPreviewButton(wxButton* previewButton)
{
	this->previewButton = previewButton;
	this->previewButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& event) {
		this->onPreviewButton();
	});
}

void PreviewController::setImageControl(wxStaticBitmap* imageControl)
{
	this->imageControl = imageControl;
}

