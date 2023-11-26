#include "HomeFrame.h"
#include "../controller/HomeFrameController.h"
#include "../controller/ImageController.h"
#include "../MenuID.h"

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
    this->imageControl = new wxStaticBitmap(this, wxID_ANY, placeholderBitmap);

    this->captureButton = new wxButton(this, wxID_ANY, "Capture");
    Bind(wxEVT_BUTTON, &HomeFrame::OnCapture, this, wxID_ANY);

    this->previewTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &HomeFrame::updateImage, this, wxID_ANY);
    this->previewTimer->Start(1000 / 30);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(this->imageControl, 1, wxALIGN_CENTER | wxALL, 5);
    mainSizer->Add(this->captureButton, 0, wxALIGN_CENTER | wxALL, 5);
    SetSizerAndFit(mainSizer);

    //=== Menu Initialization ===//
    // File Menu

    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_FILE_INSTRUMENT_SELECTION,
        "&Select Instrument", "Detect and Select instrument in use...");
    menuFile->Append(ID_FILE_SPOTFIELD_IMAGE, "&Save/Load Spotfield Image", "Save and Load spotfield bitmap file...");
    menuFile->Append(ID_FILE_MEASUREMENT_DATA, "&Save Measurement Data", "Save measurement data to file...");
    menuFile->Append(ID_FILE_CENTROID_DATA, "&Save Centroid Data", "Save centroid data to file...");
    menuFile->Append(ID_FILE_POWER_DISTRIBUTION_DATA, "&Save Power Distribution Data", "Save power distribution data to file...");
    menuFile->AppendSeparator();
    menuFile->Append(ID_FILE_CONNECT_API, "&Connect to API", "Connect to API...");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    // Setup Menu

    wxMenu* menuSetup = new wxMenu;
    menuSetup->Append(ID_SETUP_CAMERA_SETTINGS, "&Camera Settings", "Camera settings...");
    menuSetup->Append(ID_SETUP_MLA_SETTINGS, "&MLA Settings", "Microlens Array settings...");
    menuSetup->Append(ID_SETUP_MISCELLANEOUS_SETTINGS, "&Miscellaneous Settings", "Miscellaneous settings...");

    //Measurement Menu

    wxMenu* menuMeasurement = new wxMenu;
    menuMeasurement->Append(ID_MEASUREMENT_START, "&Start Measurement", "Start measurement...");
    menuMeasurement->Append(ID_MEASUREMENT_STOP, "&Stop Measurement", "Stop measurement...");
    menuMeasurement->Append(ID_MEASUREMENT_PREFERENCES, "&File Preferences", "File preferences...");
    menuMeasurement->Append(ID_MEASUREMENT_DATA, "&Save Measurement Data", "Save Measurement Data...");

    // Calibration Menu

    wxMenu* menuCalibration = new wxMenu;
    menuCalibration->Append(ID_CALIBRATION_CALIBRATE_CAMERA, "&Calibrate Camera", "Calibrate camera...");

    // Display Menu

    wxMenu* menuDisplay = new wxMenu;
    menuDisplay->Append(ID_DISPLAY_SETTINGS, "&Display Settings", "GUI Settings...");

    // Help Menu

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    //=== Menu Bar Initialization===//

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuSetup, "&Setup");
	menuBar->Append(menuMeasurement, "&Measurement");
    menuBar->Append(menuCalibration, "&Calibration");
	menuBar->Append(menuDisplay, "&Display");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to Plenoptic Camera Visualizer!"));

    //=== Menu Events Binding ===//
    // TODO: Bind events to menu items

    Bind(wxEVT_MENU, &HomeFrame::OnInstrumentSelection, this, ID_FILE_INSTRUMENT_SELECTION);
    Bind(wxEVT_MENU, &HomeFrame::OnConnectAPI, this, ID_FILE_CONNECT_API);
    Bind(wxEVT_MENU, &HomeFrame::OnCameraSettings, this, ID_SETUP_CAMERA_SETTINGS);
    Bind(wxEVT_MENU, &HomeFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &HomeFrame::OnExit, this, wxID_EXIT);

    SetSize(800, 600);
    SetBackgroundColour(wxColour(255, 255, 255));
    CenterOnScreen();

}

//=== MENU EVENTS FUNCTIONS===//

void HomeFrame::OnInstrumentSelection(wxCommandEvent& event)
{
    this->controller->onInstrumentSelection(this);
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

//=== VIEW FUNCTIONS ===//

void HomeFrame::updateImage(wxTimerEvent& event) {
    if (!controller->isWfsConnected()) {
        this->previewTimer->Stop();
		return;
	}

    wxBitmap* bitmap = new wxBitmap();
    for (BaseController* listener : this->listeners)
    {
        if (ImageController* imgController = dynamic_cast<ImageController*>(listener))
        {
            imgController->takeImage();

            if (imgController->hasError() != 0)
            {
                this->previewTimer->Stop();
                return;
            }
            bitmap = imgController->getBitmap();
        }
    }
    imageControl->SetBitmap(*bitmap);
    imageControl->Refresh();
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
