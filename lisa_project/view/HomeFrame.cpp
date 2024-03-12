#include "HomeFrame.h"
#include "../id/MenuID.h"
#include "../id/ButtonID.h"
#include "../EventDispatcher.h"
#include "InstrumentSelectionEvent.h"
#include "ExitEvent.h"


HomeFrame::HomeFrame()
    : wxFrame(NULL, wxID_ANY, "LISA - Plenoptic Camera Visualizer PCV")
{
    //=== Icon Initialization ===//

    wxBitmap iconBitmap("./img/polytech_logo.png", wxBITMAP_TYPE_PNG);
    wxIcon icon;
    icon.CopyFromBitmap(iconBitmap);
    SetIcon(icon);

    //=== Main Initialization ===//
    wxImage::AddHandler(new wxPNGHandler);
    wxBitmap placeholderBitmap("./img/lisa_logo.png", wxBITMAP_TYPE_PNG);
    this->imageControl = new wxStaticBitmap(this, wxID_ANY, placeholderBitmap, wxDefaultPosition, wxSize(512, 512));
    this->imageControl->SetDoubleBuffered(true);

    this->previewButton = new wxButton(this, ID_PREVIEW, "Start Preview");

    this->captureButton = new wxButton(this, ID_CAPTURE, "Capture");
    Bind(wxEVT_BUTTON, &HomeFrame::OnCapture, this, ID_CAPTURE);

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

    // Help Menu

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    //=== Menu Bar Initialization===//

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
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
    Bind(wxEVT_MENU, &HomeFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &HomeFrame::OnExit, this, wxID_EXIT);

    Fit();
    SetBackgroundColour(wxColour(255, 255, 255));
    CenterOnScreen();
}

//=== MENU EVENTS FUNCTIONS===//

void HomeFrame::OnInstrumentSelection(wxCommandEvent& event)
{
    EventDispatcher::Instance().PublishEvent(
        InstrumentSelectionEvent()
    );
}

void HomeFrame::OnLoadImage(wxCommandEvent& event)
{
    this->previewListener->stopPreview();
    wxImage img = this->listener->onLoadImage(this);
    if (!img.IsOk()) 
        return;
    this->setImage(&img);

}

void HomeFrame::OnConnectAPI(wxCommandEvent& event)
{
	this->listener->onConnectAPI();
}


void HomeFrame::OnCapture(wxCommandEvent& event)
{
    this->previewListener->stopPreview();
    this->listener->onCapture(this, this->imageControl->GetBitmap());
}

void HomeFrame::OnExit(wxCommandEvent& event)
{
    EventDispatcher::Instance().PublishEvent(
        ExitEvent()
    );
    exit(0);
}

void HomeFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a master's project directed LISA, Laboratory of Image Synthesis and Analysis, by the code PROJH402. This projects aims to obtain image using Thorlabs WaveFront Sensor API from a plenoptic camera.",
        "About LISA Plenoptic Camera Visualizer", wxOK | wxICON_INFORMATION);
}


//=== VIEW FUNCTIONS ===//

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
    // if the image is already in the right size, do not resize
    if (image->GetWidth() == imageControl->GetSize().GetWidth() && image->GetHeight() == imageControl->GetSize().GetHeight())
		return;

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
    return;
}



//=== UTILITY FUNCTIONS ===//

void HomeFrame::setInstrumentName(std::string instrument_name)
{
    this->instrumentName = instrument_name;
    SetStatusText(wxString::Format("Welcome to Plenoptic Camera Visualizer! - Instrument in use: %s", this->instrumentName));
}

void HomeFrame::setListener(IHomeFrameListener* listener)
{
	this->listener = listener;
}

//=== IPreviewHolder implementation ===//
wxStaticBitmap* HomeFrame::getPreviewImageControl()
{
	return this->imageControl;
}

wxButton* HomeFrame::getPreviewButton()
{
	return this->previewButton;
}

void HomeFrame::setPreviewListener(IPreviewHolderListener* listener)
{
	this->previewListener = listener;
}
