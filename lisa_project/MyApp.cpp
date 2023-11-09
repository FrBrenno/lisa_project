#include "MyApp.h"
#include "InstrumentSelectionDialog.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    //=== Controller initialization ===//

    this->homeFrameController = new HomeFrameController();
    this->instrumentController = new InstrumentController();
    this->mlaController = new MlaController();
    this->imageController = new ImageController(this->instrumentController->getInstrument());

    //=== View initialization ===//

    homeFrame = new HomeFrame();
    homeFrame->setListener(this->homeFrameController);
    homeFrame->Show(true);
    // Before Showing the software, do instrument selection
    InstrumentSelectionDialog* instrumentSelectionDialog = new InstrumentSelectionDialog(homeFrame, instrumentController);
    instrumentSelectionDialog->ShowModal();

    homeFrame->setInstrumentName(instrumentController->getInstrumentName());
    

    // this->imageController->takeImage();
    // homeFrame->updateImage(this->imageController->getImage());
    return true;
}


int MyApp::OnExit()
{
    instrumentController->closeInstrument();
	delete homeFrameController;
	delete instrumentController;
	delete mlaController;
	return 0;
}
