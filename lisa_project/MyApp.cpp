#include "MyApp.h"
#include "Event.h"
#include "EventDispatcher.h"
#include "wx/busyinfo.h"

wxIMPLEMENT_APP(MyApp);

MyApp::~MyApp()
{
    delete wfsApiService;
	delete homeFrameController;
	delete instrumentController;
	delete mlaController;
	delete imageController;
    delete homeFrame;
}

bool MyApp::OnInit()
{
    //=== WxWidgets initialization ===//
    wxImage::AddHandler(new wxPNGHandler);

    //=== WFS API initialization ===//
    this->wfsApiService = new WfsApiService();
    if (!this->wfsApiService->isApiConnectionActive())
    {
		check_api_connection();
	}

    //=== Controller initialization ===//

    this->homeFrameController = new HomeFrameController(this, this->wfsApiService);
    this->instrumentController = new InstrumentController(this, this->wfsApiService);
    this->mlaController = new MlaController(this, this->wfsApiService);
    this->imageController = new ImageController(this, this->wfsApiService, this->instrumentController->getInstrument());

    //=== View initialization ===//

    homeFrame = new HomeFrame(this->homeFrameController);
    homeFrame->addListener(this->imageController);
    homeFrame->Show(true);
    
    if (this->wfsApiService->isApiConnectionActive())
    {
        //EventDispatcher::Instance().PublishEvent(Event("InstrumentSelection"));
        // calls directly InstrumentController::onInstrumentSelection.
        // because the logic will be sequential and then, instrumentName is well defined.
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
        if (this->wfsApiService->isApiConnectionActive())
        {
            wxBusyInfo busyInfo(wxString::Format("Connected to API"));
            wxMilliSleep(timeoutMillis / 2);
			return;
		}

        wxBusyInfo busyInfo(wxString::Format("Connecting to API... Attempt %d of %d", tryCount, maxTries));
        wxMilliSleep(timeoutMillis);
    }

    wxMessageBox("Could not connect to API. Please check connection and try again.", "Error", wxOK | wxICON_ERROR);
}

