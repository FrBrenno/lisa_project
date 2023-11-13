#include "MyApp.h"
#include "InstrumentSelectionDialog.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    check_api_connection();

    //=== Controller initialization ===//

    this->homeFrameController = new HomeFrameController(this->is_wfs_connected);
    this->instrumentController = new InstrumentController(this->is_wfs_connected);
    this->mlaController = new MlaController(this->is_wfs_connected);
    this->imageController = new ImageController(this->is_wfs_connected, this->instrumentController->getInstrument());
    this->cameraSettingsController = new CameraSettingsController(this->is_wfs_connected);

    //=== View initialization ===//

    homeFrame = new HomeFrame(this->homeFrameController);
    homeFrame->Show(true);
    // Before Showing the software, do instrument selection
    if (this->is_wfs_connected) {
        InstrumentSelectionDialog* instrumentSelectionDialog = new InstrumentSelectionDialog(homeFrame, instrumentController);
        instrumentSelectionDialog->ShowModal();

        homeFrame->setInstrumentName(instrumentController->getInstrumentName());
    }
    
    

    // this->imageController->takeImage();
    // homeFrame->updateImage(this->imageController->getImage());
    return true;
}

void MyApp::check_api_connection()
{
    ViPInt32 status = VI_NULL;
    if (int err = WFS_GetStatus(VI_NULL, status)) {
        this->is_wfs_connected = false;
        return;
    }
    this->is_wfs_connected = true;
}


int MyApp::OnExit()
{
    instrumentController->closeInstrument();
	delete homeFrameController;
	delete instrumentController;
	delete mlaController;
    delete imageController;
    delete cameraSettingsController;
	return 0;
}
