#include "MyApp.h"
#include "Event.h"
#include "EventDispatcher.h"
#include "wx/busyinfo.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    //=== WxWidgets initialization ===//
    wxImage::AddHandler(new wxPNGHandler);

    //=== WFS API initialization ===//
    check_api_connection();

    //=== Controller initialization ===//

    this->homeFrameController = new HomeFrameController(this, this->is_wfs_connected);
    this->instrumentController = new InstrumentController(this, this->is_wfs_connected);
    this->mlaController = new MlaController(this, this->is_wfs_connected);
    this->imageController = new ImageController(this, this->is_wfs_connected, this->instrumentController->getInstrument());

    //=== View initialization ===//

    homeFrame = new HomeFrame(this->homeFrameController);
    homeFrame->addListener(this->imageController);
    homeFrame->Show(true);
    
    if (is_wfs_connected)
    {
        EventDispatcher::Instance().PublishEvent(Event("InstrumentSelection"));
        homeFrame->setInstrumentName(instrumentController->getInstrumentName());
    }
    
    return true;
}

void MyApp::check_api_connection()
{
    const int maxTries = 5;
    const int timeoutMillis = 1000;

    for (int tryCount = 1; tryCount <= maxTries; ++tryCount)
    {
        ViInt32 instr_count = VI_NULL;
        int err = WFS_GetInstrumentListLen(VI_NULL, &instr_count);

        if (err == VI_SUCCESS)
        {
            this->is_wfs_connected = true;
            wxBusyInfo busyInfo(wxString::Format("Connected to API"));
            wxMilliSleep(timeoutMillis / 2);
            return;
        }

        wxBusyInfo busyInfo(wxString::Format("Connecting to API... Attempt %d of %d", tryCount, maxTries));
        wxMilliSleep(timeoutMillis);
    }

    this->is_wfs_connected = false;
    wxMessageBox("Could not connect to API. Please check connection and try again.", "Error", wxOK | wxICON_ERROR);
}

