#include "HomeFrame.h"
#include "MenuID.h"

HomeFrame::HomeFrame()
    : wxFrame(NULL, wxID_ANY, "LISA - Plenoptic Camera Visualizer")
{

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
    menuFile->Append(wxID_EXIT);

    // Setup Manu
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
    SetStatusText("Welcome to Plenoptic Camera Visualizer!");

    //=== Menu Events Binding ===//
    // TODO: Bind events to menu items
    Bind(wxEVT_MENU, &HomeFrame::OnInstrumentSelection, this, ID_FILE_INSTRUMENT_SELECTION);
    Bind(wxEVT_MENU, &HomeFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &HomeFrame::OnExit, this, wxID_EXIT);
}

void HomeFrame::setListener(HomeFrameController* controller)
{
	this->listener = listener;
}

void HomeFrame::OnInstrumentSelection(wxCommandEvent& event)
{
    listener->selectInstrument();
}

void HomeFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void HomeFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a master's project directed LISA, Laboratory of Image Synthesis and Analysis, by the code PROJH402. This projects aims to obtain image using Thorlabs WaveFront Sensor API from a plenoptic camera.",
        "About LISA Plenoptic Camera Visualizer", wxOK | wxICON_INFORMATION);
}
