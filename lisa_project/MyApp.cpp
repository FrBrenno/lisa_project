#include "MyApp.h"
#include "wx/busyinfo.h"
#include "wfsApiService.h"
#include "TestWfsApiService.h"

wxIMPLEMENT_APP(MyApp);

MyApp::~MyApp()
{
    delete instrumentController;
    delete homeFrameController;
    delete wfsApiService;
    delete homeFrame;
}

bool MyApp::OnInit()
{
    //=== WxWidgets initialization ===//
    wxImage::AddHandler(new wxPNGHandler);

    //=== WFS API initialization ===//

    this->wfsApiService = new TestWfsApiService();  // Test mode: random api information
    // this->wfsApiService = new WfsApiService();    // Real mode: connect to WFS API, only works when connected
    if (!this->wfsApiService->isApiConnectionActive())
    {
		check_api_connection();
	}

    //=== View initialization ===//

    homeFrame = new HomeFrame();

    //=== Controller initialization ===//
    this->homeFrameController = new HomeFrameController(this, this->wfsApiService);
    this->instrumentController = new InstrumentController(this, this->wfsApiService);
    this->imageController = new ImageController(this, this->wfsApiService);
    this->previewController = new PreviewController(this, this->wfsApiService, this->imageController);
    
    //=== Controller-View binding ===//
    this->homeFrame->setPreviewListener(this->previewController);
    this->previewController->setImageControl(homeFrame->getPreviewImageControl());
    this->previewController->setPreviewButton(homeFrame->getPreviewButton());
    this->previewController->setCaptureButton(homeFrame->getCaptureButton());
    homeFrame->setListener(homeFrameController);
    homeFrame->Show(true);
    
    if (this->wfsApiService->isApiConnectionActive())
    {
        this->instrumentController->HandleInstrumentSelection();
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

ViSession MyApp::getInstrumentHandle()
{
	return this->instrumentController->getInstrument()->getHandle();
}

HomeFrame* MyApp::getHomeFrame()
{
	return this->homeFrame;
}
