#include "HomeFrame.h"
#include "../id/MenuID.h"
#include "../id/ButtonID.h"
#include "../EventDispatcher.h"
#include "InstrumentSelectionEvent.h"
#include "ExitEvent.h"
#include <CalibrationStartEvent.h>


HomeFrame::HomeFrame()
    : wxFrame(NULL, wxID_ANY, "LISA - Plenoptic Camera Visualizer PCV")
{
    //=== Icon Initialization ===//

    wxBitmap iconBitmap("./img/polytech_logo.png", wxBITMAP_TYPE_PNG);
    wxIcon icon;
    icon.CopyFromBitmap(iconBitmap);
    SetIcon(icon);

    //=== Main Initialization ===//
    previewPanel = new PreviewPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(previewPanel, 1, wxEXPAND | wxALL, 5);
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

    // Calibration Menu

    wxMenu* menuCalibration = new wxMenu;
    menuCalibration->Append(ID_CALIBRATION_START, "&Start Calibration", "Start calibration process...");

    // Help Menu

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    //=== Menu Bar Initialization===//

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuCalibration, "&Calibration");
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
    Bind(wxEVT_MENU, &HomeFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &HomeFrame::OnCalibrationStart, this, ID_CALIBRATION_START);
    Bind(wxEVT_MENU, &HomeFrame::OnAbout, this, wxID_ABOUT);


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
    this->previewPanel->loadImage();

}

void HomeFrame::OnConnectAPI(wxCommandEvent& event)
{
	this->listener->onConnectAPI();
}


void HomeFrame::OnCapture(wxCommandEvent& event)
{
    this->previewPanel->onCapture(this);
}

void HomeFrame::OnExit(wxCommandEvent& event)
{
    EventDispatcher::Instance().PublishEvent(
        ExitEvent()
    );
    exit(0);
}

void HomeFrame::OnCalibrationStart(wxCommandEvent& event)
{
    EventDispatcher::Instance().PublishEvent(
		CalibrationStartEvent()
	);
}

void HomeFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a master's project directed LISA, Laboratory of Image Synthesis and Analysis, by the code PROJH402. This projects aims to obtain image using Thorlabs WaveFront Sensor API from a plenoptic camera.",
        "About LISA Plenoptic Camera Visualizer", wxOK | wxICON_INFORMATION);
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

void HomeFrame::setPreviewListener(IPreviewHolderListener* listener)
{
	this->previewPanel->setPreviewListener(listener);
}

PreviewPanel* HomeFrame::getPreviewPanel()
{
	return this->previewPanel;
}
