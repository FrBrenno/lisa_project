#include "MyApp.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    //=== Controller initialization ===//
    this->homeFrameController = new HomeFrameController();
    this->instrumentController = new InstrumentController();

    //=== View initialization ===//
    homeFrame = new HomeFrame();
    homeFrame->setListener(this->homeFrameController);
    // Before Showing the software, do instrument selection
    InstrumentSelectionDialog* instrumentSelectionDialog = new InstrumentSelectionDialog(homeFrame, instrumentController);
    instrumentSelectionDialog->ShowModal();
    homeFrame->setInstrumentName(instrumentController->getInstrumentName());
    homeFrame->Show(true);

     return true;
}


