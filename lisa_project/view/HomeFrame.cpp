#include "HomeFrame.h"
#include "../controller/HomeFrameController.h"
#include "../controller/ImageController.h"
#include "../id/MenuID.h"
#include "../id/ButtonID.h"

#define PREVIEW_IMAGE_RATE 1000/2

HomeFrame::HomeFrame(HomeFrameController* controller)
    : wxFrame(NULL, wxID_ANY, "LISA - Plenoptic Camera Visualizer PCV")
{
    this->controller = controller;
    this->listeners = std::vector<BaseController*>();

    //=== Icon Initialization ===//

    wxBitmap iconBitmap("./img/polytech_logo.png", wxBITMAP_TYPE_PNG);
    wxIcon icon;
    icon.CopyFromBitmap(iconBitmap);
    SetIcon(icon);

    //=== Main Initialization ===//
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap placeholderBitmap("./img/lisa_logo.png", wxBITMAP_TYPE_PNG);
    this->imageControl = new wxStaticBitmap(this, wxID_ANY, placeholderBitmap, wxDefaultPosition, wxSize(512,512));

    this->captureButton = new wxButton(this, ID_CAPTURE, "Capture");
    Bind(wxEVT_BUTTON, &HomeFrame::OnCapture, this, ID_CAPTURE);

    this->previewButton = new wxButton(this, ID_PREVIEW, "Start Preview");
    Bind(wxEVT_BUTTON, &HomeFrame::OnPreviewButton, this, ID_PREVIEW);

    this->previewTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &HomeFrame::updateImage, this, wxID_ANY);
    this->isPreviewOn = false;

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(this->captureButton, 0, wxALIGN_CENTER | wxALL, 5);
    buttonSizer->Add(this->previewButton, 0, wxALIGN_CENTER | wxALL, 5);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(this->imageControl, 0, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);
    SetSizerAndFit(mainSizer);

    //=== Menu Initialization ===//
    // File Menu

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_FILE_INSTRUMENT_SELECTION,
        "&Select Instrument", "Detect and Select instrument in use...");
    menuFile->Append(ID_FILE_SAVE_SPOTFIELD_IMAGE, "&Save Spotfield Image", "Save spotfield bitmap file...");
    menuFile->Append(ID_FILE_LOAD_SPOTFIELD_IMAGE, "&Load Spotfield Image", "Load spotfield PNG file...");
    menuFile->AppendSeparator();
    menuFile->Append(ID_FILE_CONNECT_API, "&Connect to API", "Connect to API...");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    // Setup Menu

    wxMenu* menuSetup = new wxMenu;
    menuSetup->Append(ID_SETUP_CAMERA_SETTINGS, "&Camera Settings", "Camera settings...");

    // Help Menu

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    //=== Menu Bar Initialization===//

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuSetup, "&Setup");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to Plenoptic Camera Visualizer!"));

    //=== Menu Events Binding ===//
    // TODO: Bind events to menu items

    Bind(wxEVT_MENU, &HomeFrame::OnInstrumentSelection, this, ID_FILE_INSTRUMENT_SELECTION);
    Bind(wxEVT_MENU, &HomeFrame::OnCapture, this, ID_FILE_SAVE_SPOTFIELD_IMAGE);
    Bind(wxEVT_MENU, &HomeFrame::OnLoadImage, this, ID_FILE_LOAD_SPOTFIELD_IMAGE);
    Bind(wxEVT_MENU, &HomeFrame::OnConnectAPI, this, ID_FILE_CONNECT_API);
    Bind(wxEVT_MENU, &HomeFrame::OnCameraSettings, this, ID_SETUP_CAMERA_SETTINGS);
    Bind(wxEVT_MENU, &HomeFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &HomeFrame::OnExit, this, wxID_EXIT);

    Fit();
    SetBackgroundColour(wxColour(255, 255, 255));
    CenterOnScreen();
}

//=== MENU EVENTS FUNCTIONS===//

void HomeFrame::OnInstrumentSelection(wxCommandEvent& event)
{
    this->controller->onInstrumentSelection(this);
}

void HomeFrame::OnLoadImage(wxCommandEvent& event)
{
    this->stopPreview();
    wxImage img = this->controller->onLoadImage(this);
    // if empty image, do not change
    if (!img.IsOk()) 
        return;
    this->setImage(&img);
}

void HomeFrame::OnConnectAPI(wxCommandEvent& event)
{
	this->controller->onConnectAPI(this);
}

void HomeFrame::OnCameraSettings(wxCommandEvent& event)
{
	this->controller->onCameraSettings(this);
}

void HomeFrame::OnCapture(wxCommandEvent& event)
{
    this->controller->onCapture(this, this->imageControl->GetBitmap());
}

void HomeFrame::OnExit(wxCommandEvent& event)
{
    exit(0);
}

void HomeFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a master's project directed LISA, Laboratory of Image Synthesis and Analysis, by the code PROJH402. This projects aims to obtain image using Thorlabs WaveFront Sensor API from a plenoptic camera.",
        "About LISA Plenoptic Camera Visualizer", wxOK | wxICON_INFORMATION);
}

void HomeFrame::OnPreviewButton(wxCommandEvent& event)
{
    if (this->isPreviewOn)
    {
		this->stopPreview();
	}
    else
    {
		this->startPreview();
	}
}

//=== VIEW FUNCTIONS ===//

void HomeFrame::updateImage(wxTimerEvent& event) {
    if (!controller->isWfsConnected()) {
        this->stopPreview();
		return;
	}

    wxImage* image = new wxImage();
    for (BaseController* listener : this->listeners)
    {
        if (ImageController* imgController = dynamic_cast<ImageController*>(listener))
        {
            imgController->takeImage();

            if (imgController->hasError() != 0)
            {
                this->stopPreview();
                return;
            }
            image = imgController->getImage();
        }
    }
    this->setImage(image);
}

void HomeFrame::setImage(wxImage* image)
{
    this->imageControl->SetBitmap(wxNullBitmap);
    resizeImage(image);
    wxBitmap* bitmap = new wxBitmap(*image);
    imageControl->SetBitmap(*bitmap);
	imageControl->Refresh();
}

void HomeFrame::resizeImage(wxImage* image)
{
    int width = image->GetWidth();
    int height = image->GetHeight();
    int newWidth = imageControl->GetSize().GetWidth();
    int newHeight = imageControl->GetSize().GetHeight();
    if (width > height) {
		newHeight = (int)(newWidth * ((float)height / (float)width));
	}
    else {
		newWidth = (int)(newHeight * ((float)width / (float)height));
	}
    *image = image->Rescale(newWidth, newHeight);
}

void HomeFrame::updatePreviewButton()
{
    if (this->isPreviewOn)
    {
        if (this->controller->isWfsConnected())
        {
            this->previewButton->SetLabel("Stop Preview");
        }
        else
        {
            wxMessageBox("Cannot start preview: WFS is not connected.", "Error", wxOK | wxICON_ERROR);
        }
	}
    else
    {
		this->previewButton->SetLabel("Start Preview");
	}
}

void HomeFrame::stopPreview()
{
	this->previewTimer->Stop();
	this->isPreviewOn = false;
	this->updatePreviewButton();
}

void HomeFrame::startPreview()
{
	this->previewTimer->Start(PREVIEW_IMAGE_RATE);
	this->isPreviewOn = true;
	this->updatePreviewButton();
}
//=== UTILITY FUNCTIONS ===//

void HomeFrame::setInstrumentName(std::string instrument_name)
{
    this->instrumentName = instrument_name;
    SetStatusText(wxString::Format("Welcome to Plenoptic Camera Visualizer! - Instrument in use: %s", this->instrumentName));
}

void HomeFrame::addListener(BaseController* listener)
{
	this->listeners.push_back(listener);
}
